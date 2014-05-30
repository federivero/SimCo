
#include "ExecutionManager.h"
#include "../system/ComputationalSystem.h"
#include <stdlib.h>

ExecutionManager* ExecutionManager::instance = NULL;

ExecutionManager::ExecutionManager()
{
    
}

ExecutionManager* ExecutionManager::getInstance(){
    if (ExecutionManager::instance == NULL){
        ExecutionManager::instance = new ExecutionManager();
    }
    return ExecutionManager::instance;
}

void ExecutionManager::initialize(){
    events = new Queue<IEventCallback*>(100);
    fixedEvents = new List<IEventCallback>();
    tracer = TraceManager::getInstance();
    int upcomingEventsSize = 100;
    upcomingEvents = new Queue<Queue<IEventCallback*> *>(upcomingEventsSize);
    for (int i = 0; i < upcomingEventsSize; i++)
        upcomingEvents->queue(new Queue<IEventCallback*>(100));
    currentCycle = 0;
}

void ExecutionManager::simulate(){
    
    while(!currentExecution->finishedExecution() && (unlimitedCycles || (currentCycle < maxSimulatedCycles))){
        currentCycle++;
        tracer->traceNewCycle(currentCycle);
        // Get already scheduled events to be executed in this cycle
        events = upcomingEvents->dequeue();
        
        /* Execute fixed events */
        Iterator<IEventCallback> *it = fixedEvents->iterator();
        while(it->hasNext()){
            it->next()->simulate();
        }
        
        while (!events->isEmpty()){
            IEventCallback* currentEvent = events->dequeue();
            currentEvent->simulate();
        }
    }
    // TODO: do some work?
}

unsigned long ExecutionManager::getCurrentCycle(){
    return currentCycle;
}

void ExecutionManager::addEvent(IEventCallback* event, int cyclesToExecute){
    if (cyclesToExecute == 0){
        events->queue(event);
    }else if (cyclesToExecute > 0){
        // Queue event to appropiate cycle
        upcomingEvents->getElement(cyclesToExecute - 1)->queue(event);
    }
}

void ExecutionManager::addFixedEvent(IEventCallback* event){
    fixedEvents->add(event);
}

/* Setters */

void ExecutionManager::setUnlimitedCycles(bool unlimited){
    unlimitedCycles = unlimited;
}

void ExecutionManager::setCycleLimit(unsigned long maxCycles){
    maxSimulatedCycles = maxCycles;
}

void ExecutionManager::setComputationalSystem(ComputationalSystem* compSys){
    currentExecution = compSys;
}
