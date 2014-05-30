
#include "../simulator/ISimulable.h"
#include "../architecture/Instruction.h"
#include "Processor.h"
#include "../architecture/ISA.h"
#include "../memory/MemoryRequest.h"

Processor::Processor(unsigned long id, char* name, ISA* isa):ISimulable(id,name){
    instructionSetArchitecture = isa;
    nFlag = 0;
    vFlag = 0;
    zFlag = 0;
    cFlag = 0;
} 

/* Access methods */
ISA* Processor::getISA(){
    return instructionSetArchitecture;
}

unsigned long Processor::getPCValue(){
    return PC;
}

void Processor::setPCValue(unsigned long newValue){
    this->PC = newValue;
}

void Processor::setZFlagValue(bool newValue){
    zFlag = newValue;
}

void Processor::setNFlagValue(bool newValue){
    nFlag = newValue;
}

void Processor::setCFlagValue(bool newValue){
    cFlag = newValue;
}

void Processor::setVFlagValue(bool newValue){
    vFlag = newValue;
}

FetchStage* Processor::getFetchStage(){
    return fetchStage;
}

ExecuteStage* Processor::getExecuteStage(){
    return executeStage;
}
    


