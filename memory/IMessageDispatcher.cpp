#include "IMessageDispatcher.h"
#include "../exceptions/RuntimeException.h"

IMessageDispatcherEvent::IMessageDispatcherEvent(EventName name, IMessageDispatcher* target):eventName(name),dispatcher(target){
    
}

void IMessageDispatcherEvent::simulate(){
    switch(eventName){
        case MESSAGE_DISPATCHER_SUBMIT_MEMORY_RESPONSE:
            dispatcher->submitMemoryResponse(response,port);
            break;
        default:
            throw new RuntimeException("Inappropiate event type for IMessageDispatcherEvent");
            break;
    }
}

void MemoryDeviceEvent::setPort(InterconnectionNetwork* interface){
    port = interface;
}

void MemoryDeviceEvent::setRequest(MemoryRequest* req){
    request = req;
}

IMessageDispatcherEvent* IMessageDispatcherEvent::createEvent(EventName name, IMessageDispatcher* target, MemoryResponse* req, InterconnectionNetwork* interface){
    IMessageDispatcherEvent* e = new IMessageDispatcherEvent(name,target);
    e->setPort(interface);
    e->setRequest(req);
    return e;
}
