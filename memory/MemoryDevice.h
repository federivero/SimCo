/* 
 * File:   MemoryDevice.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 07:10 PM
 */

#ifndef MEMORYDEVICE_H
#define	MEMORYDEVICE_H

#include "IMessageDispatcher.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "MemoryChunk.h"
#include "MemoryAddress.h"
#include "../simulator/IEventCallback.h"
#include "../common/Queue.h"
#include "../common/List.h"
#include "MemoryRequest.h"
#include "MemoryResponse.h"
#include "stdio.h"

class InterconnectionNetwork;

// Inner structure to mantain information about memory requests waiting for simulated latency to pass
struct WaitingMemoryRequest{
    MemoryRequest* request;
    int cyclesToGo;
};

/* Base class for all memory devices */
class MemoryDevice : public IMessageDispatcher{
    private:        
    
    
    protected:
    
        // Number of R/W ports available on chip
        int portCount;
        // Current unused ports
        int availablePorts;
        // Ports that will become available at the beggning of the next cycle
        int freedPorts;
        // Latency in cycles of the memory responces
        int latency;

        // Stats
        unsigned long accessCount;
        unsigned long writeCount;
        unsigned long readCount;
        
        // When memory requests exceedes available ports on RAM, requests are
        // Queued to be processed on subsecuent clock cycles
        Queue<MemoryRequest> *unattendedMemoryRequests;
        // List of MemoryRequests waiting for simulated delay to end
        List<WaitingMemoryRequest> *pendingMemoryRequests;
        
        // Attends a memoryRequest, should be invoked when latency = 0
        virtual void attendMemoryRequest(MemoryRequest* requets) = 0;
        // Assigns a memory port to a request, it'll be held for 'latency' cycless
        virtual void assignPortToMemoryRequest(MemoryRequest* request) = 0;
    public:
        MemoryDevice(unsigned long id, int portNumber, int latencyCycles, char* name = 0);
        virtual void setMemoryContent(MemoryChunk* data, unsigned long address) = 0;
        virtual MemoryChunk* getMemoryContent(unsigned long address, unsigned int requestLength) = 0;
        // Submits a memory request for the event system to handle 
        virtual void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port) = 0;
        // Submits a memory Response from a lower level hierarchy 
        virtual void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port) = 0;
        
        virtual void printStatistics(ofstream* file);
};

class MemoryDeviceEvent: public IEventCallback{
    private:
        MemoryDevice* memDevice;
        MemoryRequest* request;
        InterconnectionNetwork* port;
    public:
        MemoryDeviceEvent(EventName type, MemoryDevice* device);
        void simulate();
        
        static MemoryDeviceEvent* createEvent(EventName name, MemoryDevice* device, MemoryRequest* req = NULL, InterconnectionNetwork* interface = NULL);
        
        // Setters 
        void setPort(InterconnectionNetwork* interface);
        void setRequest(MemoryRequest* req);
};
#endif	/* MEMORYCHIP_H */

