
#include "ComputationalSystem.h"
#include "../processor/Processor.h"

ComputationalSystem::ComputationalSystem(){
    
}

bool ComputationalSystem::finishedExecution(){
    return (executingProcessors == 0);
}

void ComputationalSystem::markProcessorAsFinished(){
    executingProcessors--;
}

/* Access operations */
Processor** ComputationalSystem::getProcessors(){
    return processors;
}

int ComputationalSystem::getProcessorCount(){
    return processorCount;
}

void ComputationalSystem::addProcessor(Processor* processor, int processorNumber){
    processors[processorNumber] = processor;
}

void ComputationalSystem::setProcessorCount(int processorCount){
    this->processorCount = processorCount;
    processors = new Processor*[processorCount];
    for (int i = 0; i < processorCount; i++){
        processors[i] = NULL;
    }
    executingProcessors = processorCount;
}





