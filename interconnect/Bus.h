/* 
 * File:   Bus.h
 * Author: fede
 *
 * Created on 4 de marzo de 2014, 01:29 PM
 */

#ifndef BUS_H
#define	BUS_H

#include "InterconnectionNetwork.h"
#include "../memory/IMessageDispatcher.h"
#include "../memory/MemoryRequest.h"
#include "../common/Map.h"
#include "../common/Queue.h"

// BusOwnership: stores information about the devices using this bus
struct BusOwnership{
    IMessageDispatcher* master;
    // Buses with sufficient lines support multiple request in pararlel
    int busSlotNumber;
};

/* A bus is a group of lines which broadcast its messages to all attached devices. 
 */
class Bus: public InterconnectionNetwork{
    private:
        // Pointers to devices using this bus
        IMessageDispatcher** devices;
        int deviceCount;
        // Map from meesages being sent in this bus to the owners and slots
        GenMap<MemoryRequest,BusOwnership>* currentMessages;
        // Logical bus width, dictates how many addressable messages can be sent in parallel through the bus
        unsigned int busWidth;
        int availableSlotCount;
        Queue<int>* unusedSlots;
        
        // Variable used to pass information between cycles
        int finishedRequests;
    public:
        Bus(int deviceCount);
        virtual void requestAccess(IMessageDispatcher* requester);
        virtual void submitMemoryRequest(MemoryRequest* request, IMessageDispatcher* submitter);
        virtual void submitMemoryResponse(MemoryResponse* response, IMessageDispatcher* submitter);
        virtual void initCycle();
};

#endif	/* BUS_H */

