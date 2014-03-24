
#include "ExecutionManager.h"
#include <stdlib.h>

ExecutionManager* ExecutionManager::instance = NULL;

ExecutionManager::ExecutionManager():events(new Queue<IEventCallback>(100)),fixedEvents(new List<IEventCallback>())
{
    currentCycle = 0;
}

ExecutionManager* ExecutionManager::getInstance(){
    if (ExecutionManager::instance == NULL){
        ExecutionManager::instance = new ExecutionManager();
    }
    return ExecutionManager::instance;
}

void ExecutionManager::initialize(){
    
}

void ExecutionManager::simulate(){
    
    while(!currentExecution->finishedExecution()){
        currentCycle++;
        /* Execute fixed events */
        
        
        // Get already scheduled events to be executed in this cycle
        events = upcomingEvents->dequeue();
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
        
    }
}

