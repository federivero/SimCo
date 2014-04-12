/* 
 * File:   IEventCallback.h
 * Author: fede
 *
 * Created on 5 de febrero de 2014, 07:00 PM
 */

#ifndef IEVENTCALLBACK_H
#define	IEVENTCALLBACK_H

enum EventName{
    SIMULABLE_START_CYCLE // A 'SIMULABLE_START_CYCLE' event is used to initialize data structures in each cycle
    ,INTERCONNECTION_NETWORK_EVENT_ARBITRATE_ACCESS 
    ,INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS // Used when a message entity needs access to medium
    ,INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_REQUEST
    ,INTERCONNECTION_NETWORK_EVENT_SUBMIT_MEMORY_RESPONSE
    ,MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST
    ,MESSAGE_DISPATCHER_SUBMIT_MEMORY_RESPONSE
};

/* IEventCallback: interface for hardware events to subscribe to execution
   in the main algorithm*/
class IEventCallback{
private:
protected:
    EventName eventName;
public:
    IEventCallback(EventName name):eventName(name){};
    EventName getEventName(){ return eventName; };
    virtual void simulate() = 0;
};



#endif	/* IEVENTCALLBACK_H */

