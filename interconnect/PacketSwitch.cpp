#include "PacketSwitch.h"

PacketSwitch::PacketSwitch(unsigned long deviceId, char* name, unsigned int linkNumber)
        :IMessageDispatcher(deviceId,name)
{
    linkCount = linkNumber;
    links = new P2PLink*[linkCount];
    requestedAccesses = new ListMap<InterconnectionNetwork*,bool>(linkCount);
}

void PacketSwitch::addLink(P2PLink* link, int position){
    links[position] = link;
    requestedAccesses->put(link,false);
}

void PacketSwitch::initCycle(){
    // TODO
}

void PacketSwitch::accessGranted(InterconnectionNetwork* port){
    // TODO: Check port is one of attached links. Is it worth it?
    port->submitMessage(inputBuffer->dequeue(),this);
}

void PacketSwitch::submitMessage(Message* message, InterconnectionNetwork* port){
    // TODO: Check port is one of attached links. Is it worth it?
    
}





