#include "RAM.h"
#include "../exceptions/RuntimeException.h"
#include "MemoryTable.h"
#include "../simulator/ExecutionManager.h"      

class RuntimeException;

RAM::RAM():MemoryDevice(){
    
}

RAM::RAM(unsigned long id, unsigned long capacity, int ports, int delayCount, InterconnectionNetwork* interface, char* name)
        :MemoryDevice(id, ports,delayCount,name),
        port(interface)
{
    // TODO: think of a better algorithm for the capacity
    memoryMap = MultilevelMemoryTable::createMultilevelMemoryTable(capacity,2);
    availablePorts = ports;
    initialize();
}

void RAM::initialize(){
    canceledRequests = 0;
    pendingMemoryRequests = new List<WaitingMemoryRequest*>();
    MemoryDevice::initialize();
}

// Getters & Setters:
unsigned long RAM::getCapacity(){
    return capacity;
}

void RAM::setCapacity(unsigned long capacity){
    this->capacity = capacity;
    memoryMap = MultilevelMemoryTable::createMultilevelMemoryTable(capacity,2);
}

void RAM::setPorts(int portCount){
    this->portCount = portCount;
    availablePorts = portCount;
}

void RAM::setInterface(InterconnectionNetwork* interface){
    this->port = interface;
}

void RAM::setLatency(int latency){
    this->latency = latency;
}



void RAM::initCycle(){
    int lastCycleFreedPorts = freedPorts;
    freedPorts = 0;
    // Iterate through pending memory requests and lower delay counter
    Iterator<WaitingMemoryRequest*> *it = pendingMemoryRequests->iterator();
    while(it->hasNext()){
        WaitingMemoryRequest* wmr = it->next();
        wmr->cyclesToGo--;
        if (wmr->cyclesToGo == 0){
            // If 'latency' cycles have passed, attend the request!
            it->remove();
            attendMemoryRequest(wmr->request);
        }
    }
    // if ports were freed last cycle
    availablePorts += lastCycleFreedPorts;
    while((availablePorts > 0) && (!unattendedMemoryRequests->isEmpty())){
        MemoryRequest* req = unattendedMemoryRequests->dequeue();
        assignPortToMemoryRequest(req);
    }
}

void RAM::accessGranted(InterconnectionNetwork* port){
    // Is not used for the moment
}

void RAM::submitMemoryRequest(MemoryRequest* request, InterconnectionNetwork* networkInterface){
    if (port != networkInterface){
        throw new RuntimeException("Message delivered to RAM through a non attached interface");
    }else{
        tracer->traceSubmittedMemoryRequest(id,request->getMessageId());
        if (availablePorts == 0){
            // No available ports, queue requests until next cycle
            unattendedMemoryRequests->queue(request);
        }else{
            assignPortToMemoryRequest(request);
        }
    }
}

void RAM::submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port){
    // Check for cancel operations on pending memory requests
    MemoryRequest* req = response->getMemoryRequest();
    Iterator<WaitingMemoryRequest*> *iter = pendingMemoryRequests->iterator();
    while(iter->hasNext()){
        if (iter->next()->request == req){
            iter->remove();
            canceledRequests++;
            freedPorts++;
            break;
        }
    }
    // TODO: iterate on 'unnatendedMemoryRequest'
}

void RAM::attendMemoryRequest(MemoryRequest* request){
    accessCount++;
    // Create memory response and send info through the interface
    MemoryResponse* response = new MemoryResponse(request->getMemoryAddress(),MEMORY_RESPONSE,request,this->id);
    if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
        readCount++;
        response->setRawData(memoryMap->getMemoryContent(request->getMemoryAddress(),request->getRequestSize()));
    }else if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
        writeCount++;
        // Set memory values
        memoryMap->setMemoryContent(request->getMemoryAddress(),request->getRawData());
    }
    InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE,port,this,response);
    ExecutionManager::getInstance()->addEvent(e,0);
    freedPorts++;
}

void RAM::submitMessage(Message* message, InterconnectionNetwork* port){
    MemoryRequest* req;
    switch(message->getMessageType()){
        case MEMORY_REQUEST_MEMORY_READ:
        case MEMORY_REQUEST_MEMORY_WRITE:
            req = dynamic_cast<MemoryRequest*>(message);
            submitMemoryRequest(req,port);
            break;
        case INVALIDATING_MEMORY_RESPONSE:
            submitMemoryResponse(dynamic_cast<MemoryResponse*>(message),port);
            break;
        default:
            // Ignore, broadcast messages on shared medium
            break;
            
    }
}

void RAM::assignPortToMemoryRequest(MemoryRequest* request){
    availablePorts--;
    if (latency == 1){
        // If latency = 0, attend it and send response back!
        attendMemoryRequest(request);
    }else{
        // Add memory request to latency queue
        WaitingMemoryRequest* wmr = new WaitingMemoryRequest;
        wmr->cyclesToGo = (latency-1);
        wmr->request = request;
        pendingMemoryRequests->add(wmr);
    }
}

// Non - Simulator methods

void RAM::setMemoryContent(MemoryChunk* data, unsigned long address){
    memoryMap->setMemoryContent(address,data);
}

MemoryChunk* RAM::getMemoryContent(unsigned long address, unsigned int requestLength){
    return memoryMap->getMemoryContent(address,requestLength);
}

void RAM::printStatistics(ofstream* file){
    *file << "RAM" << endl;
    MemoryDevice::printStatistics(file);
    *file << "Canceled Requests: " << canceledRequests << endl;
    *file << endl;
}

void RAM::traceSimulable(){
    tracer->traceNewRAM(this);
}


