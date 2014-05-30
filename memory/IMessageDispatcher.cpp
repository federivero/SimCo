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
        case MESSAGE_DISPATCHER_SUBMIT_MESSAGE:
            dispatcher->submitMessage(message,port);
            break;
        default:
            throw new RuntimeException("Inappropiate event type for IMessageDispatcherEvent");
            break;
    }
}

void IMessageDispatcherEvent::setPort(InterconnectionNetwork* interface){
    port = interface;
}

void IMessageDispatcherEvent::setMessage(Message* message){
    this->message = message;
}

IMessageDispatcherEvent* IMessageDispatcherEvent::createEvent(EventName name, IMessageDispatcher* target, Message* message, InterconnectionNetwork* interface){
    IMessageDispatcherEvent* e = new IMessageDispatcherEvent(name,target);
    e->setPort(interface);
    e->setMessage(message);
    return e;
}

void IMessageDispatcher::requestAccessToNetwork(InterconnectionNetwork* port){
    if (requestedAccesses->exists(port) == -1){
        throw new RuntimeException("Access requested from a dispatcher to an unattached network interface");
    }
    bool accessRequested = requestedAccesses->getData(port);
    if (accessRequested == false){
        requestedAccesses->override(port,true);
        InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                port,this,NULL);
        simulator->addEvent(e,0);
    } // Else ignore, for access has already been requested
}
