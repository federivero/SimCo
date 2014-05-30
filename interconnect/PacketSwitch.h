/* 
 * File:   Switch.h
 * Author: fede
 *
 * Created on 14 de abril de 2014, 06:03 PM
 */

#ifndef PACKETSWITCH_H
#define	PACKETSWITCH_H

class GlobalInterconnectionNetwork;

#include "../memory/IMessageDispatcher.h"
#include "RoutingAlgorithm.h"
#include "P2PLink.h"

class PacketSwitch : public IMessageDispatcher{
    
    private:
        /* Special link, connects to device */
        P2PLink* linkToDevice;
        /* Other links*/
        P2PLink** links; // Should be a hash! 
        unsigned int linkCount;
        
        Queue<Message*> *inputBuffer;
        
        /* Pointer to global network */
        GlobalInterconnectionNetwork* globalNetwork;
    public:
        // Construction Methods
        PacketSwitch(unsigned long deviceId, char* name, unsigned int linkNumber);
        void addLink(P2PLink* link, int position);    
        
        virtual void initCycle();
        virtual void submitMessage(Message* message, InterconnectionNetwork* port);
        virtual void accessGranted(InterconnectionNetwork* port);
};

#endif	/* PACKETSWITCH_H */

