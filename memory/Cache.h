/* 
 * File:   Cache.h
 * Author: fede
 *
 * Created on 3 de marzo de 2014, 09:49 PM
 */

#ifndef CACHE_H
#define	CACHE_H

#include "MemoryRequest.h"
#include "MemoryDevice.h"
#include "CacheLineEntry.h"
#include <stdlib.h>
#include "../common/Stack.h"
#include "../common/Map.h"
#include "../common/Queue.h"
#include "../common/CustomMacros.h"

enum CacheWritePolicy{
    CACHE_WRITE_WRITEBACK,
    CACHE_WRITE_WRITETHROUGH
};

enum CacheReplacementPolicy{
    CACHE_REPLACEMENT_LRU,
    CACHE_REPLACEMENT_RANDOM,
    CACHE_REPLACEMENT_FIFO
};

enum CacheCoherenceProtocol{
    CACHE_NO_COHERENCE,
    CACHE_COHERENCE_MSI,
    CACHE_COHERENCE_MESI
};

class Cache: public MemoryDevice{
    
    private:
        InterconnectionNetwork* upperMemoryHierarchyPort;
        InterconnectionNetwork* lowerMemoryHierarchyPort;
        
        // Cache Organization
        /* Cache Size = sets * associativity * lineSize 
           Line Count = sets * associativity */
        unsigned int sets;          // Number of sets in the cache
        unsigned int associativity; // Associativity of each set
        unsigned int lineSize;      // Size in bytes of each line
        
        // Cache Data
        CacheLineEntry** cacheLineEntry;

        // Policies
        CacheReplacementPolicy replacementPolicy;
        CacheWritePolicy writePolicy;
        CacheCoherenceProtocol coherenceProtocol;
        
        // Masks for the adress. This is kept here for performance,
        // since otherwise has to be calculated on every acccess
        unsigned int setMask;
        unsigned int log2setCount;
        unsigned int byteMask;
        unsigned int log2lineSize;
        
        // Queue for read requests -> maps unanswered requests from upper hierarchy to victim lines 
        GenMap<MemoryRequest*,unsigned int>* pendingLineRequests;
        // Queue for memory requests waiting to be submitted through the network, while the network
        // arbitrates access
        Queue<Message*>* lowerHierarchyAccessQueue;
        
        // Stats
        unsigned long hitCount;
        unsigned long missCount;
        unsigned long replaceCount;
        
        
        virtual void attendMemoryRequest(MemoryRequest* request);
        virtual void assignPortToMemoryRequest(MemoryRequest* request);
        
        // Internal Operations
        unsigned int getVictimLine(unsigned int set);
        void processAccessHit(MemoryRequest* request, CacheLineEntry* cacheLine, unsigned int byte);
        void dispatchCoherenceMessages(MemoryRequest* request, CacheLineEntry* cacheLine, MessageType type, bool hit);
        
        void invalidateLine(InvalidateMessage* message);
        void getTagSetAndByteFromAddress(unsigned int address, unsigned int &tag, unsigned int &set, unsigned int &byte);
        void checkAddressHit(unsigned int tag, unsigned int set, bool &hit, unsigned int &lineHit);
        void snoopRequest(MemoryRequest* request);
        void updateCoherenceState(MemoryRequest* request, CacheLineEntry* line);
    public:
        Cache(unsigned long id, unsigned int setNumber, unsigned int setAssociativity, unsigned int lineSizeInBytes, int portCount, int latency, char* name = NULL);
        void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port);
        void submitMessage(Message* message, InterconnectionNetwork* port);
        void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port);
        
        virtual void initCycle();
        
        virtual void setMemoryContent(MemoryChunk* data, unsigned long address){};
        virtual MemoryChunk* getMemoryContent(unsigned long address, unsigned int requestLength){return NULL;};
        
        virtual void accessGranted(InterconnectionNetwork* port);
        
        virtual void printStatistics(ofstream* file);
        // Setters
        void setReplacementPolicy(CacheReplacementPolicy policy);
        void setWritePolicy(CacheWritePolicy policy);
        void setCoherenceProtocol(CacheCoherenceProtocol protocol);
        void setUpperMemoryHierarchyPort(InterconnectionNetwork* upperPort);
        void setLowerMemoryHierarchyPort(InterconnectionNetwork* lowerPort);
        
        // Getters 
        unsigned int getSetCount();
        unsigned int getAssociativity();
        unsigned int getLineSize();
        CacheLineEntry* getCacheLine(int index);
        CacheReplacementPolicy getReplacementPolicy();
        CacheWritePolicy getWritePolicy();
        
};

#endif	/* CACHE_H */

