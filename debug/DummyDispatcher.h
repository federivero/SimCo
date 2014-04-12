/* 
 * File:   DummyDispatcher.h
 * Author: fede
 *
 * Created on 29 de marzo de 2014, 05:33 PM
 */

#ifndef DUMMYDISPATCHER_H
#define	DUMMYDISPATCHER_H

#include "../memory/IMessageDispatcher.h"
#include <iostream>

using namespace std;

class DummyDispatcher: public IMessageDispatcher{
    private:
    
        InterconnectionNetwork* interface;
        Queue<MemoryRequest> *unsubmittedMemoryRequests;    
    public:
        DummyDispatcher(unsigned long id):IMessageDispatcher(id){
            unsubmittedMemoryRequests = new Queue<MemoryRequest>(100);
        };
        
        void addMemoryRequest(MemoryRequest* req){
            unsubmittedMemoryRequests->queue(req);
        }
        
        virtual void initCycle(){}
        virtual void accessGranted(InterconnectionNetwork* port){
            if (!unsubmittedMemoryRequests->isEmpty()){
                MemoryRequest* request = unsubmittedMemoryRequests->dequeue();
                InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_REQUEST,
                        port,this,request);
                simulator->addEvent(e,0);
                if (!unsubmittedMemoryRequests->isEmpty()){
                    InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                        port,this);
                    simulator->addEvent(e,0);
                }
            }
        }
        virtual void submitMemoryResponse(MemoryResponse* response, InterconnectionNetwork* port){
            tracer->traceSubmittedMemoryResponse(id,response->getMessageId());
            cout << "Dummy Dispatcher " << endl;
            cout << "Received Memory Response " << endl;
            if (response->getMemoryRequest()->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
                cout << "Memory Read response" << endl;
                cout << "Address: " << response->getMemoryAdress() << endl;
                cout << "MemoryContent: ";
                response->getRawData()->print();
                cout << endl;
            }else{
                // MemoryWrite
                cout << "Memory Write Completed " << endl;
            }
        }
};

#endif	/* DUMMYDISPATCHER_H */

