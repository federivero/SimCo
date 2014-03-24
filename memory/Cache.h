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
#include <cmath>
#include <stdlib.h>
#include "../common/Stack.h"
#include "../common/Map.h"
#include "../common/Queue.h"

#define log2(x) (log((double) (x))) / (log(2.0))
#define isPowerOf2(x) ((x > 0) && (!(x & (x - 1))))

enum CacheWritePolicy{
    CACHE_WRITE_WRITEBACK,
    CACHE_WRITE_WRITETHROUGH
};

enum CacheReplacementPolicy{
    CACHE_REPLACEMENT_LRU,
    CACHE_REPLACEMENT_RANDOM,
    CACHE_REPLACEMENT_FIFO
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
        
        // Masks for the adress. This is kept here for performance,
        // since otherwise has to be calculated on every acccess
        unsigned int setMask;
        unsigned int log2setCount;
        unsigned int byteMask;
        unsigned int log2lineSize;
        
        // Queue for read requests -> maps unanswered requests from upper hierarchy to victim lines 
        GenMap<MemoryRequest,unsigned int>* pendingLineRequests;
        // Queue for dirty lines waiting to be wrote to lower hierarchy (aka: write buffer))
        Queue<MemoryRequest>* pendingDirtyLines;
        // Queue for memory reads waiting to be submitted through the network, while the network
        // arbitrates access
        Queue<MemoryRequest>* pendingMemoryReads;
        
        // Internal Operations
        unsigned int getVictimLine(unsigned int set);
    public:
        Cache(unsigned int setNumber, unsigned int setAssociativity, unsigned int lineSizeInBytes);
        void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port);
        void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port);

        virtual void setMemoryContent(MemoryChunk* data, MemoryAddress* address){};
        virtual MemoryChunk* getMemoryContent(MemoryAddress* address, InterconnectionNetwork* port){return NULL;};
        
        virtual void accessGranted(InterconnectionNetwork* port);
        
        // Setters
        void setReplacementPolicy(CacheReplacementPolicy policy);
        void setWritePolicy(CacheWritePolicy policy);
        
        // Getters 
        unsigned int getSetCount();
        unsigned int getAssociativity();
        unsigned int getLineSize();
        CacheLineEntry* getCacheLine(int index);
        CacheReplacementPolicy getReplacementPolicy();
        CacheWritePolicy getWritePolicy();
        
};

#endif	/* CACHE_H */

