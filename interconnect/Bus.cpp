#include "Bus.h"
#include "../simulator/ExecutionManager.h"
#include "stdio.h"

Bus::Bus(int devCount){
    devices = new IMessageDispatcher*[devCount];
    deviceCount = devCount;
    for (int i = 0; i < deviceCount; i++){
        devices[i] = NULL;
    }
    availableSlotCount = busWidth;
}

// TODO: this functions should hold the requester until all posible dispatchers
// had requested access and then run an arbitration function to determine
// who is the winner. In the meantime it just checks for space and answers true
// if there are available bus lines
void Bus::requestAccess(IMessageDispatcher* requester){
    if (availableSlotCount == 0){
        // Bus has no available lines! Tell requester that access is not allowed
    }else{
        availableSlotCount--;
        requester->accessGranted(this);
    }
}

void Bus::submitMemoryRequest(MemoryRequest* request, IMessageDispatcher* submitter){
    if (unusedSlots->isEmpty()){
        throw new RuntimeException("No available bus slots for memory request");
    }
    // Allocate message in software structures
    int busSlot = *unusedSlots->dequeue();
    BusOwnership b = new BusOwnership;
    b->master = submitter;
    b->busSlotNumber = busSlot;
    currentMessages->put(request,b);
    // Send message to all other devices
    for (int i = 0; i < deviceCount; i++){
        if (devices[i] != submitter){
            MemoryDevice* memDevice = dynamic_cast<MemoryDevice*>(devices[i]);
            if (memDevice != NULL){
                MemoryDeviceEvent* e = MemoryDeviceEvent::createEvent(MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST,memDevice,this,req);
                ExecutionManager::getInstance()->addEvent(e,0);
            }
        }
    }
}

void Bus::submitMemoryResponse(MemoryResponse* response, IMessageDispatcher* submitter){
    // Obtain the request that originated this response
    MemoryRequest* req = response->getMemoryRequest();
    if (!currentMessages->exists(req)){
        throw new RuntimeException("Invalid MemoryResponse: no matching request on bus");
    }else{
        BusOwnership* b = currentMessages->getData(req);
        currentMessages->remove(req);
        finishedRequests++;
        int* temporal = new int;
        *temporal = b->busSlotNumber;
        unusedSlots->queue(temporal);
        // Dispatch event to process response to all other attached devices
        for (int i = 0; i < deviceCount; i++){
            if (devices[i] != b->master){ 
                IMessageDispatcher* e = IMessageDispatcher::createEvent(MESSAGE_DISPATCHER_SUBMIT_MEMORY_RESPONSE,device[i],this,req);
                ExecutionManager::getInstance()->addEvent(e,0);
            }
        }
    }
}

void Bus::initCycle(){
    
}


