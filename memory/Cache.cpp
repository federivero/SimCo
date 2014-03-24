
#include "Cache.h"
#include "../exceptions/IllegalCacheArgumentException.h"
#include "../exceptions/UnalignedMemoryAccessException.h"
#include "../exceptions/RuntimeException.h"
#include "../simulator/ExecutionManager.h"
#include <iostream>

using namespace std;

Cache::Cache(unsigned int s, unsigned int a, unsigned int ls){
    if (!isPowerOf2(s)){
        throw new IllegalCacheArgumentException("Set number must be a power of 2 ");
    }
    if (!isPowerOf2(ls)){
        throw new IllegalCacheArgumentException("Line Size must be a power of 2");
    }
    this->sets = s;
    this->associativity = a;
    this->lineSize = ls;
    log2lineSize = log2(ls);
    log2setCount = log2(s);
    byteMask = ((1 << ((int) log2lineSize)) - 1);
    if (sets > 1){
        setMask = ((1 << (int)(log2(sets))) - 1) << log2lineSize;
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
    
    pendingLineRequests = new ListMap<MemoryRequest,unsigned int>(10); 
    pendingDirtyLines = new Queue<MemoryRequest>(10);
}

void Cache::submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port){
    if (port == upperMemoryHierarchyPort){
        // MemoryRequest comming from upper memory hiearchy (or CPU)
        unsigned int adress = request->getMemoryAdress();
        unsigned int byte = byteMask & adress;
        unsigned int set = 0;
        unsigned int tag = ((adress - set) - byte) >> (log2lineSize + log2setCount);
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
                hit = true;
                cacheLine = cacheLineEntry[i]->getLineData();
            }
        }
        if (hit){
            if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ || 
                request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
                if ((byte + request->getRequestSize()) > lineSize){
                    throw new UnalignedMemoryAccessException("");
                }
                if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
                    MemoryChunk* data = new MemoryChunk(&cacheLine[byte],request->getRequestSize());
                    if (replacementPolicy == CACHE_REPLACEMENT_LRU){
                        cacheLineEntry[i]->setTimestamp(ExecutionManager::getInstance()->getCurrentCycle());
                    }
                    // TODO: Trigger event to return memory adress
                }else{
                    // MEMORY_REQUEST_MEMORY_WRITE
                    MemoryChunk* writeData = request->getRawData();
                    for (int j = 0; j < writeData->getBytesLength(); j++){
                        cacheLine[byte + j] = writeData->getBytes()[j];
                    }
                    if (writePolicy == CACHE_WRITE_WRITEBACK){
                        cacheLineEntry[i]->setDirty(true);
                        cacheLineEntry[i]->setTimestamp(ExecutionManager::getInstance()->getCurrentCycle());
                    }else{
                        // TODO: Triger event to write data on lower level hierarchy
                    }
                }
            } // Else throw illegal message?
        }else{
            // Cache Miss: determine victim and ask lower hierarchy for the block!
            unsigned int victimLine = getVictimLine(set);
            unsigned int blockStartAdress = (tag << (log2lineSize + log2setCount)) | 
                                            (set << (log2lineSize)); // Ignore byte
            MemoryRequest* req = new MemoryRequest(blockStartAdress,lineSize,MEMORY_REQUEST_MEMORY_READ);
            // Save request until response arrives, mapped to victim line number )
            pendingLineRequests->put(req,&victimLine);
            // Reqest access to bus and hold request until access is granted
            InterconnectionNetworkEvent* e = new InterconnectionNetworkEvent(
                INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                lowerMemoryHierarchyPort,this);
            ExecutionManager::getInstance()->addEvent(e,0);
            pendingMemoryReads->queue(req);
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
                }
                // if memory is dirty, submit write event to lower memory
                if (cacheLineEntry[lineToReplace]->isDirty()){
                    unsigned int dirtyLineAdress = cacheLineEntry[lineToReplace]->getTag() << (log2lineSize + log2setCount) | 
                                                   ((lineToReplace / sets) << (log2lineSize));
                    MemoryRequest* dirtyLineReq = new MemoryRequest(dirtyLineAdress,log2setCount,MEMORY_REQUEST_MEMORY_WRITE);
                    dirtyLineReq->setRawData(new MemoryChunk(cacheLineEntry[lineToReplace]->getLineData(),log2lineSize));
                    pendingDirtyLines->queue(dirtyLineReq);
                    // TODO:: Trigger event to write to lower memory
                }
                // Copy memory from response to line
                response->getRawData()->copyTo(cacheLineEntry[lineToReplace]->getLineData());
                // Compute original memoryResponse and trigger event to send memoryBack
            }else{
                // Broadcast message in lower hierarchy: ignore
            }
    }else{
        // Ignore, could be broadcast message in upper port
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

unsigned int Cache::getVictimLine(unsigned int set){
    unsigned int victimLine = -1;
    int startIndex = set * associativity;
    int endIndex = startIndex + associativity - 1; 
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
}

void Cache::setReplacementPolicy(CacheReplacementPolicy policy){
    replacementPolicy = policy;
}

void Cache::setWritePolicy(CacheWritePolicy policy){
    writePolicy = policy;
}

void Cache::accessGranted(InterconnectionNetwork* port){
    if (port == upperMemoryHierarchyPort || port == lowerMemoryHierarchyPort){
        // Add event to send memory request
        InterconnectionNetworkEvent* e = new InterconnectionNetworkEvent(
                INTERCONNECTION_NETWORK_EVENT_SEND_MESSAGE,
                port,this);
        if (pendingMemoryReads->isEmpty()){
            throw new RuntimeException("Empty queue of messages for access to bus");
        }
        e->setMemoryRequest(pendingMemoryReads->dequeue());
        ExecutionManager::getInstance()->addEvent(e,0);
        
    }else{
        // Throw exception
    }
}









