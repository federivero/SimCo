
#include "MemoryDevice.h"


MemoryDeviceEvent::MemoryDeviceEvent(EventName type, MemoryDevice* device):IEventCallback(type),memDevice(device){
}

void MemoryDeviceEvent::simulate(){
    switch(eventName){
        case EVENT_INIT_CYCLE:
            break;
        case MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST:
            memDevice->submitMemoryRequest(request,port);
            break;
        default:
            break;
    }
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

