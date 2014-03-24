/* 
 * File:   ExecutionManager.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 11:48 AM
 */

#ifndef EXECUTIONMANAGER_H
#define	EXECUTIONMANAGER_H

#include "../system/ComputationalSystem.h"
#include "IEventCallback.h"
#include "../common/Queue.h"
#include "../common/List.h"

class ExecutionManager{
private:
    /* Pointer to computational system described in the configuration.
     Simulation is implemented as two computational systems (see documentation)*/
    ComputationalSystem* currentExecution;
    
    // Computer Cycle Number
    unsigned long currentCycle;
    
    /* Queue of events to simulate */
    Queue<IEventCallback> *events;
    /* Queue of events to be simultad on every cycle*/
    List<IEventCallback> *fixedEvents;
    /* Queue of events to be simulated on next Cycles */
    Queue<Queue<IEventCallback> > *upcomingEvents;
    
    static ExecutionManager* instance;
    ExecutionManager();
    
public:
    static ExecutionManager* getInstance();
    // The initialize function schedules initial events for the simulator to run
    void initialize();
    void simulate();
    unsigned long getCurrentCycle();
    
    void addEvent(IEventCallback* event, int cyclesToExecute);
};

#endif	/* EXECUTIONMANAGER_H */

