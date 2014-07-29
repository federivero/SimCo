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
    // Constructors
    InterconnectionNetwork();
    InterconnectionNetwork(unsigned long id);
    virtual void initialize() = 0;
    
    MemoryResponse* getAdress(MemoryRequest* adress);
    virtual void requestAccess(IMessageDispatcher* requester);
    virtual void submitMessage(Message* message, IMessageDispatcher* submitter) = 0;
    //virtual void submitMemoryResponse(MemoryResponse* response, IMessageDispatcher* submitter) = 0;
    //void arbitrateAccess(IMessageDispatcher* requester);
    
    // Function to add a device to the network
    virtual void addDevice(IMessageDispatcher* device, int deviceNumber) = 0;
    virtual void setDeviceCount(int deviceCount){};
};

/*PRE: cyclesToExecute > 0*/
class InterconnectionNetworkEvent: public IEventCallback{
    private:
        InterconnectionNetwork* network;
        IMessageDispatcher* submitter;
        Message* message;
    public:
        InterconnectionNetworkEvent(EventName name, InterconnectionNetwork* inetwork, IMessageDispatcher* irequester);
        void simulate();
        
        static InterconnectionNetworkEvent* createEvent(EventName name, 
                                                        InterconnectionNetwork* net, IMessageDispatcher* dispatcher = 0, Message* message = 0);
        
        // Setters
        void setMessage(Message* message);
};

#endif	/* INTERCONNECTIONNETWORK_H */

