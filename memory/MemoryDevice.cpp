
#include "MemoryDevice.h"
#include <sstream>

MemoryDevice::MemoryDevice(unsigned long id, int portNumber, int latencyCycles, char* name)
        :IMessageDispatcher(id,name),
        portCount(portNumber),
        latency(latencyCycles)
{
    unattendedMemoryRequests = new Queue<MemoryRequest*>(portNumber * latency);
    freedPorts = 0;
    // Initialize stats
    accessCount = 0;
    writeCount = 0;
    readCount = 0;
}

MemoryDeviceEvent::MemoryDeviceEvent(EventName type, MemoryDevice* device):IEventCallback(type),memDevice(device){
}

void MemoryDeviceEvent::simulate(){
    switch(eventName){
        case MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST:
            memDevice->submitMemoryRequest(request,port);
            break;
            /*
        case MEMORY_DEVICE_PROCESS_MEMORY_REQUEST:
            memDevice->processMemoryRequest(request);
             */
        default:
            break;
    }
}

void MemoryDevice::printStatistics(ofstream* file){
    ISimulable::printStatistics(file);
    *file << "MemoryDevice Accesses: " << accessCount << endl;
    *file << "MemoryDevice Reads:    " << readCount << endl;
    *file << "MemoryDevice Writes:   " << writeCount << endl;
}

void MemoryDeviceEvent::setPort(InterconnectionNetwork* interface){
    port = interface;
}

void MemoryDeviceEvent::setRequest(MemoryRequest* req){
    request = req;
}

MemoryDeviceEvent* MemoryDeviceEvent::createEvent(EventName name, MemoryDevice* device, MemoryRequest* req, InterconnectionNetwork* interface){
    MemoryDeviceEvent* e = new MemoryDeviceEvent(name,device);
    e->setPort(interface);
    e->setRequest(req);
    return e;
}

