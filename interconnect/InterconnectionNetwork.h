/* 
 * File:   InterconnectionNetwork.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:49 AM
 */

#ifndef INTERCONNECTIONNETWORK_H
#define	INTERCONNECTIONNETWORK_H

#include "../simulator/ISimulable.h"
#include "../system/ComputationalSystem.h"
#include "../memory/MemoryRequest.h"
#include "../memory/MemoryResponse.h"
#include "../simulator/IEventCallback.h"
#include "../memory/IMessageDispatcher.h"
#include "../interconnect/Message.h"
#include "../simulator/TraceManager.h"

class IMessageDispatcher;
class ComputationalSystem;

class InterconnectionNetwork: public ISimulable{
private:
    ComputationalSystem* system;
public:
    InterconnectionNetwork(unsigned long id);
    MemoryResponse* getAdress(MemoryRequest* adress);
    virtual void requestAccess(IMessageDispatcher* requester);
    virtual void submitMemoryRequest(MemoryRequest* request, IMessageDispatcher* submitter) = 0;
    virtual void submitMemoryResponse(MemoryResponse* response, IMessageDispatcher* submitter) = 0;
    //void arbitrateAccess(IMessageDispatcher* requester);
};

/*PRE: cyclesToExecute > 0*/
class InterconnectionNetworkEvent: public IEventCallback{
    private:
        InterconnectionNetwork* network;
        IMessageDispatcher* submitter;
        MemoryRequest* request;
        MemoryResponse* response;
    public:
        InterconnectionNetworkEvent(EventName name, InterconnectionNetwork* inetwork, IMessageDispatcher* irequester);
        void simulate();
        
        static InterconnectionNetworkEvent* createEvent(EventName name, 
                                                        InterconnectionNetwork* net, IMessageDispatcher* dispatcher = 0, 
                                                        MemoryRequest* req = NULL, MemoryResponse* res = NULL);
        
        // Setters
        void setMemoryRequest(MemoryRequest* m);
        void setMemoryResponse(MemoryResponse* m);
};

#endif	/* INTERCONNECTIONNETWORK_H */

