/* 
 * File:   MemoryChip.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 07:10 PM
 */

#ifndef MEMORYDEVICE_H
#define	MEMORYDEVICE_H

#include "MemoryChunk.h"
#include "MemoryAddress.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "../simulator/IEventCallback.h"
#include "MemoryRequest.h"
#include "MemoryResponse.h"
#include "IMessageDispatcher.h"
#include "stdio.h"

class InterconnectionNetwork;

/* Base class for all memory devices */
class MemoryDevice: public IMessageDispatcher{
private:
        
public:
    virtual void setMemoryContent(MemoryChunk* data, MemoryAddress* address) = 0;
    virtual MemoryChunk* getMemoryContent(MemoryAddress* address, InterconnectionNetwork* port) = 0;
    // Submits a memory request for the event system to handle 
    virtual void submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* port) = 0;
    // Submits a memory Response from a lower level hierarchy 
    virtual void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port) = 0;
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

