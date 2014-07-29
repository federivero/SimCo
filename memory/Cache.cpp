
#include "Cache.h"
#include "../exceptions/IllegalCacheArgumentException.h"
#include "../exceptions/UnalignedMemoryAccessException.h"
#include "../exceptions/RuntimeException.h"
#include "../simulator/ExecutionManager.h"
#include <iostream>

using namespace std;

Cache::Cache(){
    
}

Cache::Cache(unsigned long id, unsigned int s, unsigned int a, unsigned int ls, int portCount, int delayClocks, char* name)
        :MemoryDevice(id, portCount,delayClocks,name)
{
    setSetCount(s);
    setAssociativity(a);
    setLineSize(ls);
    initialize();
}

void Cache::initialize(){
    log2lineSize = intlog2(lineSize);
    log2setCount = intlog2(sets);
    byteMask = ((1 << ((int) log2lineSize)) - 1);
    if (sets > 1){
        setMask = ((1 << log2setCount) - 1) << log2lineSize;
    }else{
        setMask = 0;
    }
    unsigned int lineCount = sets * associativity;
    cacheLineEntry = new CacheLineEntry*[lineCount];
    for (int i = 0; i < lineCount; i++){
        cacheLineEntry[i] = NULL;
    }
    
    // Initialize stats
    hitCount = 0;
    missCount = 0;
    replaceCount = 0;
    
    pendingLineRequests = new ListMap<MemoryRequest*,unsigned int>(10); 
    lowerHierarchyAccessQueue = new Queue<Message*>(10);
    upperMemoryHierarchyPort = NULL;
    lowerMemoryHierarchyPort = NULL;
    requestedAccesses = new ListMap<InterconnectionNetwork*,bool>(1);
    MemoryDevice::initialize();
}

void Cache::submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port){
    if (port == upperMemoryHierarchyPort){
        accessCount++;
        if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
            readCount++;
        }else if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
            writeCount++;
        }
        // MemoryRequest comming from upper memory hiearchy (or CPU)
        unsigned int address = request->getMemoryAddress();
        unsigned int tag, set, byte;
        getTagSetAndByteFromAddress(address,tag,set,byte);
        // Search on set for tag
        bool hit; unsigned int lineHit;
        checkAddressHit(tag,set,hit,lineHit);
        if (hit){
            hitCount++;
            dispatchCoherenceMessages(request,cacheLineEntry[lineHit],request->getMessageType(),hit);
            processAccessHit(request,cacheLineEntry[lineHit],byte);
            tracer->traceCacheLineChange(id,lineHit,cacheLineEntry[lineHit]);
        }else{
            missCount++;
            // Cache Miss: determine victim and ask lower hierarchy for the block!
            unsigned int victimLine = getVictimLine(set);
            if (cacheLineEntry[victimLine] != NULL) // if not a new block
                dispatchCoherenceMessages(request,cacheLineEntry[victimLine],request->getMessageType(),hit);
            unsigned int blockStartAdress = (tag << (log2lineSize + log2setCount)) | 
                                            (set << (log2lineSize)); // Ignore byte
            MemoryRequest* req = new MemoryRequest(blockStartAdress,lineSize,MEMORY_REQUEST_MEMORY_READ,this->id);
            req->setOriginalRequest(request);
            // Save request until response arrives, mapped to victim line number )
            pendingLineRequests->put(request,victimLine);
            // Request access to bus and hold request until access is granted
            tracer->traceNewMemoryRequest(req->getMessageId(),req->getMemoryAddress(),req->getMessageType());
            requestAccessToNetwork(lowerMemoryHierarchyPort);
            lowerHierarchyAccessQueue->queue(req);
        }
    }else{
        snoopRequest(request);
    }
}

void Cache::snoopRequest(MemoryRequest* request){
    // Lower request broadcast to memory all memory
    unsigned int address = request->getMemoryAddress();
    unsigned int tag, set, byte;
    getTagSetAndByteFromAddress(address,tag,set,byte);
    bool hit; unsigned int lineHit;
    checkAddressHit(tag,set,hit,lineHit);
    if (hit){
         InvalidatingMemoryResponse* resp;
         MemoryChunk* rawData;
         unsigned char* data;
         switch(coherenceProtocol){
             case CACHE_COHERENCE_MSI:
                 switch(cacheLineEntry[lineHit]->getState()){
                     case CACHE_LINE_MODIFIED:
                         // Access to modified line, set as shared, provide value and invalidate lower memory resonse!
                         resp = new InvalidatingMemoryResponse(address,INVALIDATING_MEMORY_RESPONSE,request,this->id);
                         data = new unsigned char[request->getRequestSize()];
                         rawData = new MemoryChunk(data,request->getRequestSize());
                         rawData->copyFrom(&cacheLineEntry[lineHit]->getLineData()[byte]);
                         resp->setRawData(rawData);
                         lowerMemoryHierarchyPort->submitMessage(resp,this);
                         if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
                             cacheLineEntry[lineHit]->setCacheLineState(CACHE_LINE_SHARED);
                             tracer->traceCacheLineChange(id,lineHit,cacheLineEntry[lineHit]);
                         }
                     case CACHE_LINE_SHARED:
                         // if its a write mesage, cache line state should be invalid 
                         if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
                             cacheLineEntry[lineHit]->setCacheLineState(CACHE_LINE_INVALID);
                             tracer->traceCacheLineChange(id,lineHit,cacheLineEntry[lineHit]);
                         }
                         break;
                     default:
                         break;
                 }
             case CACHE_COHERENCE_MESI:
                 // TODO
                 break;
             default:
                 break;
         }
    }
}

void Cache::submitMessage(Message* message, InterconnectionNetwork* port){
    switch(message->getMessageType()){
        case MEMORY_RESPONSE:
        case INVALIDATING_MEMORY_RESPONSE:
            if (port == lowerMemoryHierarchyPort)
                submitMemoryResponse(dynamic_cast<MemoryResponse*>(message),port);
            break;
        case MEMORY_REQUEST_MEMORY_READ:
        case MEMORY_REQUEST_MEMORY_WRITE:
            if (port == upperMemoryHierarchyPort)
                submitMemoryRequest(dynamic_cast<MemoryRequest*>(message),port);
            break;
        case CACHE_COHERENCE_INVALIDATE:
            if (port == lowerMemoryHierarchyPort)
                invalidateLine(dynamic_cast<InvalidateMessage*>(message));
            break;
        default:
            break;
    }
}

void Cache::invalidateLine(InvalidateMessage* message){
    unsigned int address = message->getInvalidateAddress();
    unsigned int tag, set, byte;
    getTagSetAndByteFromAddress(address,tag,set,byte);
    int startIndex = set * associativity;
    int endIndex = (set + 1) * associativity;
    // Search all lines where the block could be and invalidate them!
    for (int i = startIndex; i < endIndex; i++){
        if (cacheLineEntry[i] != NULL && (cacheLineEntry[i]->getTag() == tag)){
            cacheLineEntry[i]->setCacheLineState(CACHE_LINE_INVALID);
            tracer->traceCacheLineChange(id,i,cacheLineEntry[i]);
        }
    }
}

void Cache::submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port){
    if (port == lowerMemoryHierarchyPort){
            // MemoryResponse comming from lower memory hiearchy 
            MemoryRequest* originalRequest = response->getMemoryRequest()->getOriginalRequest();
            int pendingMemoryRequestIndex = pendingLineRequests->exists(originalRequest);
            if (pendingMemoryRequestIndex != -1){
                unsigned int lineToReplace = pendingLineRequests->getData(originalRequest);
                // TODO: Check this
                pendingLineRequests->remove(originalRequest);
                if (cacheLineEntry[lineToReplace]==NULL){
                    cacheLineEntry[lineToReplace] = new CacheLineEntry(lineSize);
                }else{
                    replaceCount++;
                }
                // if memory is dirty, submit write event to lower memory
                if (cacheLineEntry[lineToReplace]->isDirty()){
                    // Have to form line address with info got
                    unsigned int setBits = (lineToReplace / associativity);
                    unsigned int dirtyLineAdress = cacheLineEntry[lineToReplace]->getTag() << (log2lineSize + log2setCount) | 
                                                   (setBits << (log2lineSize));
                    MemoryRequest* dirtyLineReq = new MemoryRequest(dirtyLineAdress,log2setCount,MEMORY_REQUEST_MEMORY_WRITE,this->id);
                    // TODO: infinite write buffers
                    // TODO: Major memory leaks
                    unsigned char* data = new unsigned char[lineSize];
                    MemoryChunk* rawData = new MemoryChunk(data,lineSize);
                    rawData->copyFrom(cacheLineEntry[lineToReplace]->getLineData());
                    dirtyLineReq->setRawData(rawData);
                    lowerHierarchyAccessQueue->queue(dirtyLineReq);
                    requestAccessToNetwork(lowerMemoryHierarchyPort);
                    tracer->traceNewMemoryRequest(dirtyLineReq->getMessageId(),dirtyLineReq->getMemoryAddress(),dirtyLineReq->getMessageType());
                }
                // Copy memory from response to line
                response->getRawData()->copyTo(cacheLineEntry[lineToReplace]->getLineData());
                // Copy TAG onto cacheLineEntry
                cacheLineEntry[lineToReplace]->setTag(originalRequest->getMemoryAddress() >> (log2lineSize + log2setCount));
                // Has new content, no longer dirty
                cacheLineEntry[lineToReplace]->setDirty(false);
                // Now the access is a hit! Process it as so
                // TODO: erase request to lower hiearchy
                unsigned int byte = byteMask & originalRequest->getMemoryAddress();
                processAccessHit(originalRequest,cacheLineEntry[lineToReplace],byte);
                // Trace cache change
                tracer->traceCacheLineChange(id,lineToReplace,cacheLineEntry[lineToReplace]);
            }else{
                // Broadcast message in lower hierarchy: ignore
            }
    }else{
        // Ignore, could be broadcast message in upper port
    }
}

void Cache::processAccessHit(MemoryRequest* request, CacheLineEntry* cacheLine, unsigned int byte){
    unsigned char* cacheLineData = cacheLine->getLineData();
    if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ || 
        request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
        if ((byte + request->getRequestSize()) > lineSize){
            throw new UnalignedMemoryAccessException("Multiple cache line access");
        }
        MemoryResponse* response = new MemoryResponse(request->getMemoryAddress(),MEMORY_RESPONSE,request,this->id);
        if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
            MemoryChunk* data = new MemoryChunk(&cacheLineData[byte],request->getRequestSize());
            if (replacementPolicy == CACHE_REPLACEMENT_LRU){
                cacheLine->setTimestamp(ExecutionManager::getInstance()->getCurrentCycle());
            }
            response->setRawData(data);
        }else{
            // MEMORY_REQUEST_MEMORY_WRITE
            MemoryChunk* writeData = request->getRawData();
            writeData->copyTo(&cacheLine->getLineData()[byte]);
            cacheLine->setTimestamp(ExecutionManager::getInstance()->getCurrentCycle());
            if (writePolicy == CACHE_WRITE_WRITEBACK){
                cacheLine->setDirty(true);
            }else if (writePolicy == CACHE_WRITE_WRITETHROUGH){
                MemoryRequest* writeRequest = new MemoryRequest(request->getMemoryAddress(),request->getRawData()->getBytesLength(),MEMORY_REQUEST_MEMORY_WRITE,this->id);
                writeRequest->setRawData(request->getRawData());
                tracer->traceNewMemoryRequest(writeRequest->getMessageId(),writeRequest->getMemoryAddress(),writeRequest->getMessageType());
                requestAccessToNetwork(lowerMemoryHierarchyPort);
                lowerHierarchyAccessQueue->queue(writeRequest);
            }
        }
        updateCoherenceState(request,cacheLine);
        InterconnectionNetworkEvent* responseEvent = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE,
                upperMemoryHierarchyPort,this,response);
        simulator->addEvent(responseEvent,0);
    } // Else throw illegal message?
}

void Cache::updateCoherenceState(MemoryRequest* request, CacheLineEntry* line){
    switch(coherenceProtocol){
        case CACHE_COHERENCE_MSI:
            if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
                line->setCacheLineState(CACHE_LINE_MODIFIED);
            }else if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
                if (line->getState() == CACHE_LINE_INVALID){
                    line->setCacheLineState(CACHE_LINE_SHARED);
                }  
            }
            break;
        case CACHE_COHERENCE_MESI:
            break;
    }
}

unsigned int Cache::getSetCount(){
    return sets;
}

unsigned int Cache::getAssociativity(){
    return associativity;
}

unsigned int Cache::getLineSize(){
    return lineSize;
}

CacheLineEntry* Cache::getCacheLine(int index){
    return cacheLineEntry[index];
}

CacheWritePolicy Cache::getWritePolicy(){
    return writePolicy;
}

void Cache::checkAddressHit(unsigned int tag, unsigned int set, bool& hit, unsigned int& lineHit){
    // Search on set for tag
    hit = false;
    int startIndex = set * associativity;
    int endIndex = (set + 1) * associativity;
    for (lineHit = startIndex; lineHit < endIndex; lineHit++){
        if (cacheLineEntry[lineHit] != NULL && (cacheLineEntry[lineHit]->getTag() == tag)){
            // if a coherence protocol is used, then the block cannot be invalid
            if ((coherenceProtocol == CACHE_NO_COHERENCE) || (cacheLineEntry[lineHit]->getState() != CACHE_LINE_INVALID)){
                hit = true;
                break;
            }
        }
    }
}
unsigned int Cache::getVictimLine(unsigned int set){
    unsigned int victimLine = -1;
    int startIndex = set * associativity;
    int endIndex = startIndex + associativity - 1;
    // First check for an unused or invalid line
    for (unsigned int i = startIndex; i <= endIndex;  i++){
        if (cacheLineEntry[i] == NULL || (cacheLineEntry[i]->getState() == CACHE_LINE_INVALID)){
            return i;
        }
    }       
    switch(replacementPolicy){
        case CACHE_REPLACEMENT_FIFO:
            // TODO
            break;
        case CACHE_REPLACEMENT_RANDOM:
            // Random replacement policy, choose at random!
            victimLine = rand() % (associativity) + (set * associativity);
            break;
        case CACHE_REPLACEMENT_LRU:
            // LRU: Check for smallest timestamp
            unsigned long smallestTimestamp = cacheLineEntry[startIndex]->getTimestamp();
            victimLine = startIndex;
            for (int i = startIndex + 1; i <= endIndex;  i++){
                unsigned long actualTimestamp = cacheLineEntry[i]->getTimestamp();
                if (actualTimestamp < smallestTimestamp){
                    smallestTimestamp = actualTimestamp;
                    victimLine = startIndex;
                }
            }        
            break;
    }
    return victimLine;
}

void Cache::getTagSetAndByteFromAddress(unsigned int address, unsigned int& tag, unsigned int& set, unsigned int& byte){
    byte = byteMask & address;
    set = 0;
    tag = address >> (log2lineSize + log2setCount);
    if (sets != 1){
        // not fully associative
        set = (setMask & address) >> log2lineSize;
    }
}

void Cache::printStatistics(ofstream* file){
    *file << "Memory Cache" << endl;
    MemoryDevice::printStatistics(file);
    *file << "Hit Count:   " << hitCount << endl;
    *file << "Miss Count:  " << missCount << endl; 
    *file << "Repl. Count: " << replaceCount << endl << endl;
}

void Cache::traceSimulable(){
    tracer->traceNewCache(this);
}

void Cache::setSetCount(unsigned int setCount){
    if (!isPowerOf2(setCount)){
        throw new IllegalCacheArgumentException("Set number must be a power of 2 ");
    }
    this->sets = setCount;
}

void Cache::setLineSize(unsigned int lineSize){
    if (!isPowerOf2(lineSize)){
        throw new IllegalCacheArgumentException("Line Size must be a power of 2");
    }
    this->lineSize = lineSize;
}

void Cache::setAssociativity(unsigned int associativity){
    this->associativity = associativity;
}

void Cache::setPortCount(unsigned int portCount){
    this->portCount = portCount;
}

void Cache::setLatency(unsigned int latency){
    this->latency = latency;    
}

void Cache::setReplacementPolicy(CacheReplacementPolicy policy){
    replacementPolicy = policy;
}

void Cache::setWritePolicy(CacheWritePolicy policy){
    writePolicy = policy;
}

void Cache::setCoherenceProtocol(CacheCoherenceProtocol protocol){
    coherenceProtocol = protocol;
}

void Cache::setUpperMemoryHierarchyPort(InterconnectionNetwork* upperPort){
    upperMemoryHierarchyPort = upperPort;
}

void Cache::setLowerMemoryHierarchyPort(InterconnectionNetwork* lowerPort){
    lowerMemoryHierarchyPort = lowerPort;
    requestedAccesses->put(lowerMemoryHierarchyPort,false);
}

void Cache::accessGranted(InterconnectionNetwork* port){
    if (port == upperMemoryHierarchyPort || port == lowerMemoryHierarchyPort){
        // Add event to send memory request
        InterconnectionNetworkEvent* e = new InterconnectionNetworkEvent(
                INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE,
                port,this);
        if (lowerHierarchyAccessQueue->isEmpty()){
            throw new RuntimeException("Empty queue of messages for access to bus");
        }
        e->setMessage(lowerHierarchyAccessQueue->dequeue());
        ExecutionManager::getInstance()->addEvent(e,0);
        requestedAccesses->override(lowerMemoryHierarchyPort,false);
        // if queue is not empty, request access again!
        if (!lowerHierarchyAccessQueue->isEmpty())
            requestAccessToNetwork(lowerMemoryHierarchyPort);
    }else{
        throw new RuntimeException("Access granted from a non attached network");
    }
}

void Cache::initCycle(){
    // TODO
}

void Cache::attendMemoryRequest(MemoryRequest* request){
    // TODO
}

void Cache::assignPortToMemoryRequest(MemoryRequest* request){
    // TODO
}

void Cache::dispatchCoherenceMessages(MemoryRequest* request, CacheLineEntry* cacheLine, MessageType type, bool hit){
    switch(coherenceProtocol){
        case CACHE_COHERENCE_MSI:
            switch(cacheLine->getState()){
                case CACHE_LINE_SHARED:
                    if ((type == MEMORY_REQUEST_MEMORY_WRITE) && hit){
                        // Write on a shared block, place invalidate message!
                        InvalidateMessage* invalidateMessage = new InvalidateMessage(request->getMemoryAddress(),CACHE_COHERENCE_INVALIDATE,this->id);
                        requestAccessToNetwork(lowerMemoryHierarchyPort);
                        lowerHierarchyAccessQueue->queue(invalidateMessage);
                    }
                    break;
                case CACHE_LINE_INVALID:
                    // Do not do anything, regular miss
                    break;
                case CACHE_LINE_MODIFIED:
                    // Dont do anything, regular hit or write miss
                    break;
                default:
                    break;
            }
            break;
        case CACHE_COHERENCE_MESI:
            // TODO
            break;
        default:
            break;
    }
}




