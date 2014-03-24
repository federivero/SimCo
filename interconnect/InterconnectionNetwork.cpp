
#include "InterconnectionNetwork.h"
#include "../exceptions/UnsuportedEventException.h"
#include <stdlib.h>

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
        :IEventCallback(name),network(inetwork),requester(irequester){
    
}

void InterconnectionNetworkEvent::simulate(){
    switch(eventName){
        case INTERCONNECTION_NETWORK_EVENT_ARBITRATE_ACCESS:
            network->requestAccess(requester);
            break;
        case INTERCONNECTION_NETWORK_EVENT_SEND_MESSAGE:
            network->submitMemoryRequest(request,requester);
            break;
        default:
            throw new UnsuportedEventException("Event not an InterconnectionNetworkEvent");
    }
}

void InterconnectionNetworkEvent::setMemoryRequest(MemoryRequest* m){
    request = m;
}

