/* 
 * File:   InterconnectionNetwork.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:49 AM
 */

#ifndef INTERCONNECTIONNETWORK_H
#define	INTERCONNECTIONNETWORK_H

#include "../system/ComputationalSystem.h"
#include "../memory/MemoryRequest.h"
#include "../memory/MemoryResponse.h"
#include "../simulator/IEventCallback.h"
#include "../memory/IMessageDispatcher.h"
#include "../interconnect/Message.h"
#include "../simulator/ISimulable.h"

class IMessageDispatcher;
class ComputationalSystem;

class InterconnectionNetwork: public ISimulable{
private:
    ComputationalSystem* system;
public:
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
        IMessageDispatcher* requester;
        MemoryRequest* request;
    public:
        InterconnectionNetworkEvent(EventName name, InterconnectionNetwork* inetwork, IMessageDispatcher* irequester);
        void simulate();
        
        void setMemoryRequest(MemoryRequest* m);
};

#endif	/* INTERCONNECTIONNETWORK_H */

