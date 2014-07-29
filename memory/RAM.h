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
        
        // Stats
        unsigned int canceledRequests;
        
        virtual void attendMemoryRequest(MemoryRequest* request);
        virtual void assignPortToMemoryRequest(MemoryRequest* request);
    public:
        // Constructors:
        RAM();
        RAM(unsigned long id, unsigned long capacity, int ports, int latency, InterconnectionNetwork* interface, char* name = 0);
        void initialize();
        
        // Getters & Setters
        unsigned long getCapacity();
        void setCapacity(unsigned long capacity);
        void setPorts(int portCount);
        void setLatency(int latency);
        void setInterface(InterconnectionNetwork* interface);
        
        
        // Direct memory content operations 
        void setMemoryContent(MemoryChunk* data, unsigned long address);
        MemoryChunk* getMemoryContent(unsigned long address, unsigned int requestLength);
        
        // Simulation operations
        void initCycle();
        void accessGranted(InterconnectionNetwork* port);
        void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port);
        void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port);
        void submitMessage(Message* message, InterconnectionNetwork* port);
        
        void printStatistics(ofstream* file);
        void traceSimulable();
};

#endif	/* RAM_H */

