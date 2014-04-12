#include "Bus.h"
#include "../simulator/ExecutionManager.h"
#include "../exceptions/RuntimeException.h"
#include "../memory/MemoryDevice.h"
#include "stdio.h"

Bus::Bus(unsigned long id, int devCount, int width):InterconnectionNetwork(id){
    devices = new IMessageDispatcher*[devCount];
    deviceCount = devCount;
    for (int i = 0; i < deviceCount; i++){
        devices[i] = NULL;
    }
    busWidth = width;
    availableSlotCount = busWidth;
    currentMessages = new ListMap<MemoryRequest,BusOwnership>(100);
    unusedSlots = new Queue<int>(busWidth);
    for (int i = 0; i < busWidth; i++){
        unusedSlots->queue(new int);
    }   
    unattendedAccessRequests = new Queue<IMessageDispatcher>(100);
    freedSlots = 0;
}

// TODO: this functions should hold the requester until all posible dispatchers
// had requested access and then run an arbitration function to determine
// who is the winner. In the meantime it just checks for space and answers true
// if there are available bus lines
void Bus::requestAccess(IMessageDispatcher* requester){
    if (availableSlotCount == 0){
        // Bus has no available lines! Tell requester that access is not allowed
        unattendedAccessRequests->queue(requester);
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
    BusOwnership* b = new BusOwnership;
    b->master = submitter;
    b->busSlotNumber = busSlot;
    currentMessages->put(request,b);
    // Send request to all other devices (if they can process them)
    for (int i = 0; i < deviceCount; i++){
        if (devices[i] != submitter){
            MemoryDevice* memDevice = dynamic_cast<MemoryDevice*>(devices[i]);
            if (memDevice != NULL){
                MemoryDeviceEvent* e = MemoryDeviceEvent::createEvent(MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST,memDevice,request,this);
                ExecutionManager::getInstance()->addEvent(e,0);
            }
        }
    }
}

void Bus::submitMemoryResponse(MemoryResponse* response, IMessageDispatcher* submitter){
    // Obtain the request that originated this response
    MemoryRequest* req = response->getMemoryRequest();
    if (currentMessages->exists(req) == -1){
        throw new RuntimeException("Invalid MemoryResponse: no matching request on bus");
    }else{
        BusOwnership* b = currentMessages->getData(req);
        currentMessages->remove(req);
        finishedRequests++;
        int* temporal = new int;
        *temporal = b->busSlotNumber;
        unusedSlots->queue(temporal);
        freedSlots++;
        // Dispatch event to process response to all other attached devices
        for (int i = 0; i < deviceCount; i++){
            if (devices[i] != submitter){ 
                IMessageDispatcherEvent* e = IMessageDispatcherEvent::createEvent(MESSAGE_DISPATCHER_SUBMIT_MEMORY_RESPONSE,devices[i],response,this);
                ExecutionManager::getInstance()->addEvent(e,0);
            }
        }
    }
}

void Bus::initCycle(){
    availableSlotCount += freedSlots;
    freedSlots = 0;
    while((availableSlotCount > 0) && (!unattendedAccessRequests->isEmpty())){
        availableSlotCount--;
        unattendedAccessRequests->dequeue()->accessGranted(this);
    }
}

/* Construction Methods */

// Attachs a device to the bus, this function should only be called during initialization
void Bus::addDevice(IMessageDispatcher* device, unsigned int deviceNumber){
    devices[deviceNumber] = device;
}


