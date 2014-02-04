
#include "ExecutionManager.h"

ExecutionManager::ExecutionManager()
{
    
}

void ExecutionManager::execute(){
    while(!currentExecution->finishedExecution()){
        currentExecution->advanceClock(nextClockExecution);
        currentExecution = nextClockExecution;
    }
    // TODO: do some work?
}


