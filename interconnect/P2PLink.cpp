#include "P2PLink.h"


P2PLink::P2PLink(unsigned long id, IMessageDispatcher* firstPoint, IMessageDispatcher* secondPoint)
        :InterconnectionNetwork(id) {
    this->firstPoint = firstPoint;
    this->secondPoint = secondPoint;
}

void P2PLink::requestAccess(IMessageDispatcher* requester){
    
}

void P2PLink::submitMessage(Message* message, IMessageDispatcher* submitter){
    
}

