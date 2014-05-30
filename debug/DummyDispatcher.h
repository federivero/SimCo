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

struct ScheduledMemoryRequests{
    long scheduledCycle;
    List<MemoryRequest> *memoryRequests;
};

class DummyDispatcher: public IMessageDispatcher{
    private:
    
        InterconnectionNetwork* interface;
        Queue<MemoryRequest*> *unsubmittedMemoryRequests;
        List<ScheduledMemoryRequests> *scheduledMemoryRequests;
        
    public:
        DummyDispatcher(unsigned long id):IMessageDispatcher(id){
            unsubmittedMemoryRequests = new Queue<MemoryRequest*>(100);
            scheduledMemoryRequests = new List<ScheduledMemoryRequests>();
        };
        
        void addMemoryRequest(MemoryRequest* req){
            unsubmittedMemoryRequests->queue(req);
        }
        
        void queueMemoryRequest(MemoryRequest* req, long dispatchCycle){
            Iterator<ScheduledMemoryRequests> *iter = scheduledMemoryRequests->iterator();
            bool found = false;
            while(iter->hasNext()){
                ScheduledMemoryRequests* actual = iter->next();
                if (actual->scheduledCycle == dispatchCycle){
                    found = true;
                    actual->memoryRequests->add(req);
                    break;
                }
            }
            if (!found){
                ScheduledMemoryRequests* smr = new ScheduledMemoryRequests;
                smr->memoryRequests = new List<MemoryRequest>();
                smr->memoryRequests->add(req);
                smr->scheduledCycle = dispatchCycle;
                scheduledMemoryRequests->add(smr);
            }
        }
        
        virtual void accessGranted(InterconnectionNetwork* port){
            if (!unsubmittedMemoryRequests->isEmpty()){
                MemoryRequest* request = unsubmittedMemoryRequests->dequeue();
                InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE,
                        port,this,request);
                simulator->addEvent(e,0);
                if (!unsubmittedMemoryRequests->isEmpty()){
                    InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                        port,this);
                    simulator->addEvent(e,0);
                }
            }
        }
        virtual void submitMessage(Message* message, InterconnectionNetwork* port){
            if (message->getMessageType() == MEMORY_RESPONSE){
                MemoryResponse* response = dynamic_cast<MemoryResponse*>(message);
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
            
        }
        
        virtual void initCycle(){
            // Check schedule List for 
            long actualCycle = simulator->getCurrentCycle();
            Iterator<ScheduledMemoryRequests> *iter = scheduledMemoryRequests->iterator();
            while (iter->hasNext()){
                ScheduledMemoryRequests* smr = iter->next();
                if (smr->scheduledCycle == actualCycle){
                    iter->remove();
                    Iterator<MemoryRequest> *iterMR = smr->memoryRequests->iterator();
                    while(iterMR->hasNext()){
                        unsubmittedMemoryRequests->queue(iterMR->next());
                    }
                    InterconnectionNetworkEvent* e = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                        interface,this);
                    simulator->addEvent(e,0);
                    break;
                }
            }
            
        }
        
        void setInterface(InterconnectionNetwork* port){
            interface = port;
        }
};

#endif	/* DUMMYDISPATCHER_H */

