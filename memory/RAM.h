/* 
 * File:   RAM.h
 * Author: fede
 *
 * Created on 24 de marzo de 2014, 10:40 PM
 */

#ifndef RAM_H
#define	RAM_H

#include "MemoryDevice.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "../common/Queue.h"
#include "MemoryRequest.h"
#include "MemoryResponse.h"
#include "MemoryTable.h"

class RAM: public MemoryDevice{
    private:
        // Capacity in bytes
        long capacity;
        
        // Memory contents
        MemoryTable* memoryMap;
        
        // Pointer to the network interface
        InterconnectionNetwork* port;
        
        virtual void attendMemoryRequest(MemoryRequest* request);
        virtual void assignPortToMemoryRequest(MemoryRequest* request);
    public:
        RAM(unsigned long id, unsigned long capacity, int ports, int latency, InterconnectionNetwork* interface, char* name = 0);
        
        virtual void setMemoryContent(MemoryChunk* data, unsigned long address);
        virtual MemoryChunk* getMemoryContent(unsigned long address, unsigned int requestLength);
        virtual void initCycle();
        virtual void accessGranted(InterconnectionNetwork* port);
        virtual void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port);
        virtual void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port);
        
        virtual void printStatistics(ofstream* file);
};

#endif	/* RAM_H */

