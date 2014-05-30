/* 
 * File:   IMessageDispatcher.h
 * Author: fede
 *
 * Created on 17 de marzo de 2014, 11:13 PM
 */

#ifndef IMESSAGEDISPATCHER_H
#define	IMESSAGEDISPATCHER_H

#include "../simulator/IEventCallback.h"
#include "../simulator/ISimulable.h"
#include "../interconnect/Message.h"
#include "MemoryResponse.h"
#include "../common/Map.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "stdio.h"

class InterconnectionNetwork;

class IMessageDispatcher: public ISimulable{
    private:
        
    protected:
        GenMap<InterconnectionNetwork*,bool> *requestedAccesses;
    public:
        IMessageDispatcher(unsigned long id, char* name = NULL);
        virtual void initCycle() = 0;
        virtual void accessGranted(InterconnectionNetwork* port) = 0;
        virtual void submitMessage(Message* message, InterconnectionNetwork* port) = 0;
        void requestAccessToNetwork(InterconnectionNetwork* port);
};

class IMessageDispatcherEvent: public IEventCallback{
    private:
        IMessageDispatcher* dispatcher;
        InterconnectionNetwork* port;
        Message* message;
    public:
        IMessageDispatcherEvent(EventName name, IMessageDispatcher* target);
        
        static IMessageDispatcherEvent* createEvent(EventName name, IMessageDispatcher* target, Message* message, InterconnectionNetwork* interface = NULL);
        void simulate();
        
        // Setters 
        void setPort(InterconnectionNetwork* interface);
        void setMessage(Message* message);
};

#endif	/* IMESSAGEDISPATCHER_H */

