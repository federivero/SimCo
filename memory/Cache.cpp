
#include "Cache.h"
#include "../exceptions/IllegalCacheArgumentException.h"
#include "../exceptions/UnalignedMemoryAccessException.h"
#include "../exceptions/RuntimeException.h"
#include "../simulator/ExecutionManager.h"
#include <iostream>

using namespace std;

Cache::Cache(unsigned long id, unsigned int s, unsigned int a, unsigned int ls, int portCount, int delayClocks, char* name)
        :MemoryDevice(id, portCount,delayClocks,name)
{
    if (!isPowerOf2(s)){
        throw new IllegalCacheArgumentException("Set number must be a power of 2 ");
    }
    if (!isPowerOf2(ls)){
        throw new IllegalCacheArgumentException("Line Size must be a power of 2");
    }
    this->sets = s;
    this->associativity = a;
    this->lineSize = ls;
    log2lineSize = intlog2(ls);
    log2setCount = intlog2(s);
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
    upperMemoryHierarchyPort = NULL;
    lowerMemoryHierarchyPort = NULL;
    requestedAccesses = new ListMap<InterconnectionNetwork,bool>(1);
    
    pendingLineRequests = new ListMap<MemoryRequest,unsigned int>(10); 
    lowerHierarchyAccessQueue = new Queue<MemoryRequest>(10);
  
    // Initialize stats
    hitCount = 0;
    missCount = 0;
    replaceCount = 0;
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
        unsigned int adress = request->getMemoryAdress();
        unsigned int byte = byteMask & adress;
        unsigned int set = 0;
        unsigned int tag = adress >> (log2lineSize + log2setCount);
        if (sets != 1){
            // not fully associative
            set = (setMask & adress) >> log2lineSize;
        }
        // Search on set for tag
        bool hit = false;
        unsigned char* cacheLine = NULL;
        int startIndex = set * associativity;
        int endIndex = (set + 1) * associativity;
        int i;
        for (i = startIndex; i < endIndex; i++){
            if (cacheLineEntry[i] != NULL && (cacheLineEntry[i]->getTag() == tag)){
                // if a coherence protocol is used, then the block cannot be invalid
                if ((coherenceProtocol == CACHE_NO_COHERENCE) || (cacheLineEntry[i]->getState() != CACHE_LINE_INVALID)){
                    hit = true;
                    cacheLine = cacheLineEntry[i]->getLineData();
                    break;
                }
            }
        }
        if (hit){
            hitCount++;
            processAccessHit(request,cacheLineEntry[i],byte);
        }else{
            missCount++;
            // Cache Miss: determine victim and ask lower hierarchy for the block!
            unsigned int victimLine = getVictimLine(set);
            unsigned int blockStartAdress = (tag << (log2lineSize + log2setCount)) | 
                                            (set << (log2lineSize)); // Ignore byte
            MemoryRequest* req = new MemoryRequest(blockStartAdress,lineSize,MEMORY_REQUEST_MEMORY_READ);
            req->setOriginalRequest(request);
            // TODO: Use integer pool
            unsigned int* aux = new unsigned int;
            *aux = victimLine;
            // Save request until response arrives, mapped to victim line number )
            pendingLineRequests->put(request,aux);
            // Request access to bus and hold request until access is granted
            tracer->traceNewMemoryRequest(req->getMessageId(),req->getMemoryAdress(),req->getMessageType());
            requestAccessToNetwork(lowerMemoryHierarchyPort);
            lowerHierarchyAccessQueue->queue(req);
        }
    }else{
        // use this as bus snooping?
    }
}

void Cache::submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port){
    if (port == lowerMemoryHierarchyPort){
            // MemoryResponse comming from lower memory hiearchy 
            MemoryRequest* originalRequest = response->getMemoryRequest()->getOriginalRequest();
            int pendingMemoryRequestIndex = pendingLineRequests->exists(originalRequest);
            if (pendingMemoryRequestIndex != -1){
                unsigned int lineToReplace = *(pendingLineRequests->getData(originalRequest));
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
                    MemoryRequest* dirtyLineReq = new MemoryRequest(dirtyLineAdress,log2setCount,MEMORY_REQUEST_MEMORY_WRITE);
                    // TODO: Major memory leaks
                    unsigned char* data = new unsigned char[lineSize];
                    MemoryChunk* rawData = new MemoryChunk(data,lineSize);
                    rawData->copyFrom(cacheLineEntry[lineToReplace]->getLineData());
                    dirtyLineReq->setRawData(rawData);
                    lowerHierarchyAccessQueue->queue(dirtyLineReq);
                    requestAccessToNetwork(lowerMemoryHierarchyPort);
                    tracer->traceNewMemoryRequest(dirtyLineReq->getMessageId(),dirtyLineReq->getMemoryAdress(),dirtyLineReq->getMessageType());
                }
                // Copy memory from response to line
                response->getRawData()->copyTo(cacheLineEntry[lineToReplace]->getLineData());
                // Copy TAG onto cacheLineEntry
                cacheLineEntry[lineToReplace]->setTag(originalRequest->getMemoryAdress() >> (log2lineSize + log2setCount));
                // Has new content, no longer dirty
                cacheLineEntry[lineToReplace]->setDirty(false);
                // Now the access is a hit! Process it as so
                // TODO: erase request to lower hiearchy
                unsigned int byte = byteMask & originalRequest->getMemoryAdress();
                processAccessHit(originalRequest,cacheLineEntry[lineToReplace],byte);
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
        MemoryResponse* response = new MemoryResponse(request->getMemoryAdress(),MEMORY_RESPONSE,request);
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
                MemoryRequest* writeRequest = new MemoryRequest(request->getMemoryAdress(),request->getRawData()->getBytesLength(),MEMORY_REQUEST_MEMORY_WRITE);
                writeRequest->setRawData(request->getRawData());
                tracer->traceNewMemoryRequest(writeRequest->getMessageId(),writeRequest->getMemoryAdress(),writeRequest->getMessageType());
                requestAccessToNetwork(lowerMemoryHierarchyPort);
                lowerHierarchyAccessQueue->queue(writeRequest);
            }
        }
        InterconnectionNetworkEvent* responseEvent = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_RESPONSE,
                upperMemoryHierarchyPort,this,NULL,response);
        simulator->addEvent(responseEvent,0);
    } // Else throw illegal message?
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

void Cache::printStatistics(ofstream* file){
    *file << "Memory Cache" << endl;
    MemoryDevice::printStatistics(file);
    *file << "Hit Count:   " << hitCount << endl;
    *file << "Miss Count:  " << missCount << endl; 
    *file << "Repl. Count: " << replaceCount << endl << endl;
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
    bool* b = new bool; *b = false;
    requestedAccesses->put(lowerMemoryHierarchyPort,b);
}

void Cache::accessGranted(InterconnectionNetwork* port){
    if (port == upperMemoryHierarchyPort || port == lowerMemoryHierarchyPort){
        // Add event to send memory request
        InterconnectionNetworkEvent* e = new InterconnectionNetworkEvent(
                INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_REQUEST,
                port,this);
        if (lowerHierarchyAccessQueue->isEmpty()){
            throw new RuntimeException("Empty queue of messages for access to bus");
        }
        e->setMemoryRequest(lowerHierarchyAccessQueue->dequeue());
        ExecutionManager::getInstance()->addEvent(e,0);
        *requestedAccesses->getData(lowerMemoryHierarchyPort) = false;
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
                        /*
                        // Write on a shared block, place invalidate message!
                        Message* invalidateMessage = new Message(CACHE_COHERENCE_INVALIDATE);
                        requestAccessToNetwork(lowerMemoryHierarchyPort);
                        lowerHierarchyAccessQueue->queue(writeRequest);
                         * */
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




