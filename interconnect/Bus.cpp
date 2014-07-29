#include "Bus.h"
#include "../simulator/ExecutionManager.h"
#include "../exceptions/RuntimeException.h"
#include "../memory/MemoryDevice.h"
#include "stdio.h"

Bus::Bus(){
    
}

Bus::Bus(unsigned long id, char* name, int devCount, int width):InterconnectionNetwork(id){
    transfersPerCycle = width;
    this->name = name;
    deviceCount = devCount;
    initialize();
}

void Bus::setDeviceCount(int devCount){
    this->deviceCount = devCount;
}

void Bus::initialize(){
    devices = new IMessageDispatcher*[deviceCount];
    deviceCount = deviceCount;
    for (int i = 0; i < deviceCount; i++){
        devices[i] = NULL;
    }
    availableSlotCount = transfersPerCycle;
    currentMessages = new ListMap<MemoryRequest*,BusOwnership*>(100);
    unusedSlots = new Queue<int>(transfersPerCycle);
    for (int i = 0; i < transfersPerCycle; i++){
        unusedSlots->queue(i);
    }   
    unattendedAccessRequests = new Queue<IMessageDispatcher*>(deviceCount);
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

void Bus::submitMessage(Message* message, IMessageDispatcher* submitter){
    switch(message->getMessageType()){
        case MEMORY_REQUEST_MEMORY_READ:
        case MEMORY_REQUEST_MEMORY_WRITE:
            submitMemoryRequest(dynamic_cast<MemoryRequest*>(message),submitter);
            break;
        case MEMORY_RESPONSE:
        case INVALIDATING_MEMORY_RESPONSE:
            submitMemoryResponse(dynamic_cast<MemoryResponse*>(message),submitter);
            break;
        case CACHE_COHERENCE_INVALIDATE:
            submitInfoMessage(message,submitter);
            break;
        default:
            break;
    }
    tracer->traceSubmittedMessageToBus(this,message);
}

void Bus::submitInfoMessage(Message* message, IMessageDispatcher* submitter){
    broadcastMessage(message,submitter);
    freedSlots++;
}

void Bus::broadcastMessage(Message* message, IMessageDispatcher* submitter){
    for (int i = 0; i < deviceCount; i++){
        if (devices[i] != submitter){ 
            IMessageDispatcherEvent* e = IMessageDispatcherEvent::createEvent(MESSAGE_DISPATCHER_SUBMIT_MESSAGE,devices[i],message,this);
            ExecutionManager::getInstance()->addEvent(e,0);
        }
    }
}

void Bus::submitMemoryRequest(MemoryRequest* request, IMessageDispatcher* submitter){
    if (unusedSlots->isEmpty()){
        throw new RuntimeException("No available bus slots for memory request");
    }
    // A memory request on a non-pipelined bus holds the bus until the response arrives
    int busSlot = unusedSlots->dequeue();
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
        unusedSlots->queue(b->busSlotNumber);
        freedSlots++;
        // Dispatch event to process response to all other attached devices
        broadcastMessage(response,submitter);
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

/* Getters */

unsigned int Bus::getTransfersPerCycle(){
    return transfersPerCycle;
}

void Bus::setTransfersPerCycle(int transfersPerCycle){
    this->transfersPerCycle = transfersPerCycle;
}

/* Construction Methods */

// Attachs a device to the bus, this function should only be called during initialization
void Bus::addDevice(IMessageDispatcher* device, int deviceNumber){
    devices[deviceNumber] = device;
    deviceNumber++;
}

/* ISimulable operations */
void Bus::printStatistics(ofstream* file){
    // TODO
}

void Bus::traceSimulable(){
    tracer->traceNewBus(this);
}


