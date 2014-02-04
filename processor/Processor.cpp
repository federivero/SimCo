
#include "Processor.h"

void Processor::advanceClock(Processor* retValue){
    for (int i = 0; i < pipelineStageCount; i++){
        pipelineStages[i].simulateStage(retValue->getPipelineStage(i));
    }
}

PipelineStage* Processor::getPipelineStage(int pipeStageNumber){
    return (&pipelineStages[pipeStageNumber]);
}

ISA* Processor::getISA(){
    return instructionSetArchitecture;
}


