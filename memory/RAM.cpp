#include "RAM.h"
#include "../exceptions/RuntimeException.h"
#include "MemoryTable.h"
#include "../simulator/ExecutionManager.h"      

class RuntimeException;

RAM::RAM(unsigned long id, unsigned long capacity, int ports, int delayCount, InterconnectionNetwork* interface, char* name)
        :MemoryDevice(id, ports,delayCount,name),
        port(interface)
{
    // TODO: think of a better algorithm for the capacity
    memoryMap = MultilevelMemoryTable::createMultilevelMemoryTable(capacity,2);
    pendingMemoryRequests = new List<WaitingMemoryRequest>();
    availablePorts = ports;
}

void RAM::initCycle(){
    int lastCycleFreedPorts = freedPorts;
    freedPorts = 0;
    // Iterate through pending memory requests and lower delay counter
    Iterator<WaitingMemoryRequest> *it = pendingMemoryRequests->iterator();
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
    // RAM shouldn't care about other memory responses (in certain organizations, it can't happen)
}

void RAM::attendMemoryRequest(MemoryRequest* request){
    accessCount++;
    // Create memory response and send info through the interface
    MemoryResponse* response = new MemoryResponse(request->getMemoryAdress(),MEMORY_RESPONSE,request);
    if (request->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
        readCount++;
        response->setRawData(memoryMap->getMemoryContent(request->getMemoryAdress(),request->getRequestSize()));
    }else if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
        writeCount++;
        // Set memory values
        memoryMap->setMemoryContent(request->getMemoryAdress(),request->getRawData());
    }
    InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_RESPONSE,port,this,NULL,response);
    ExecutionManager::getInstance()->addEvent(e,0);
    freedPorts++;
}

// Non - Simulator methods

void RAM::setMemoryContent(MemoryChunk* data, unsigned long address){
    
}

MemoryChunk* RAM::getMemoryContent(unsigned long address, unsigned int requestLength){
    return NULL;
}

void RAM::printStatistics(ofstream* file){
    *file << "RAM" << endl;
    MemoryDevice::printStatistics(file);
    *file << endl;
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




