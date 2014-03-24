/* 
 * File:   IMessageDispatcher.h
 * Author: fede
 *
 * Created on 17 de marzo de 2014, 11:13 PM
 */

#ifndef IMESSAGEDISPATCHER_H
#define	IMESSAGEDISPATCHER_H

#include "../interconnect/InterconnectionNetwork.h"
#include "../interconnect/Message.h"
#include "MemoryResponse.h"
#include "stdio.h"

class InterconnectionNetwork;

class IMessageDispatcher{
    private:
        
    public:
        virtual void accessGranted(InterconnectionNetwork* port) = 0;
        virtual void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port) = 0;
};

class IMessageDispatcherEvent: public IEventCallback{
    private:
        IMessageDispatcher* dispatcher;
        InterconnectionNetwork* port;
        MemoryResponse* response;
    public:
        IMessageDispatcherEvent(EventName name, IMessageDispatcher* target);
        
        static IMessageDispatcherEvent* createEvent(EventName name, IMessageDispatcher* target, MemoryResponse* req = NULL, InterconnectionNetwork* interface = NULL);
        void simulate();
        
        // Setters 
        void setPort(InterconnectionNetwork* interface);
        void setRequest(MemoryResponse* req);
};

#endif	/* IMESSAGEDISPATCHER_H */

