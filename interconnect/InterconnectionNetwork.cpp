
#include "InterconnectionNetwork.h"
#include "../exceptions/UnsuportedEventException.h"
#include <stdlib.h>

InterconnectionNetwork::InterconnectionNetwork(unsigned long id):ISimulable(id){
    
}

MemoryResponse* InterconnectionNetwork::getAdress(MemoryRequest* adress){
    return NULL;
}

void InterconnectionNetwork::requestAccess(IMessageDispatcher* requester){
    // TODO: Implement on descendants (should be an abstract method)
    requester->accessGranted(this);
}

/*
void InterconnectionNetwork::arbitrateAccess(IMessageDispatcher* requester){
    // TODO: Implement on descendants (should be an abstract method)
    requester->accessGranted(this);
   
}
*/


/* InterconnectionNetworkEvents! */

InterconnectionNetworkEvent::InterconnectionNetworkEvent
        (EventName name, InterconnectionNetwork* inetwork, IMessageDispatcher* irequester)
        :IEventCallback(name),network(inetwork),submitter(irequester){
    
}

void InterconnectionNetworkEvent::simulate(){
    switch(eventName){
        case INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS:
            network->requestAccess(submitter);
            break;
        case INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE:
            network->submitMessage(message,submitter);
            break;
        default:
            throw new UnsuportedEventException("Event not an InterconnectionNetworkEvent");
    }
}

InterconnectionNetworkEvent* InterconnectionNetworkEvent::createEvent(EventName name,
        InterconnectionNetwork* net, IMessageDispatcher* dispatcher,
        Message* message){
    
    InterconnectionNetworkEvent* event = new InterconnectionNetworkEvent(name,net,dispatcher);
    event->setMessage(message);
    return event;
}
        
void InterconnectionNetworkEvent::setMessage(Message* message){
    this->message = message;
}
