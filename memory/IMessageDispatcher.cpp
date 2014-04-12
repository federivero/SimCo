#include "IMessageDispatcher.h"
#include "../exceptions/RuntimeException.h"
#include "../simulator/IEventCallback.h"

/* IMessageDispatcher */

IMessageDispatcher::IMessageDispatcher(unsigned long id, char* name):ISimulable(id,name){
    
}


/* IMessageDispatcherEvents */

IMessageDispatcherEvent::IMessageDispatcherEvent(EventName name, IMessageDispatcher* target):IEventCallback(name),dispatcher(target)
{
    
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

void IMessageDispatcherEvent::setPort(InterconnectionNetwork* interface){
    port = interface;
}

void IMessageDispatcherEvent::setResponse(MemoryResponse* resp){
    response = resp;
}

IMessageDispatcherEvent* IMessageDispatcherEvent::createEvent(EventName name, IMessageDispatcher* target, MemoryResponse* resp, InterconnectionNetwork* interface){
    IMessageDispatcherEvent* e = new IMessageDispatcherEvent(name,target);
    e->setPort(interface);
    e->setResponse(resp);
    return e;
}

void IMessageDispatcher::requestAccessToNetwork(InterconnectionNetwork* port){
    bool* accessRequested = requestedAccesses->getData(port);
    if (accessRequested == NULL){
        throw new RuntimeException("Access requested from a dispatcher to an unattached network interface");
    }
    if (*accessRequested == false){
        *accessRequested = true;
        InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                port,this,NULL,NULL);
        simulator->addEvent(e,0);
    } // Else ignore, for access has already been requested
}
