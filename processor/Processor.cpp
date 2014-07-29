
#include "../system/ComputationalSystem.h"
#include "../simulator/ISimulable.h"
#include "../architecture/Instruction.h"
#include "Processor.h"
#include "../architecture/ISA.h"
#include "../memory/MemoryRequest.h"

Processor::Processor(){
    executedInstructions = 0;
    jumpInstructions;
    aluInstructions;
    memoryInstructions;
}

Processor::Processor(unsigned long id, char* name, ISA* isa):ISimulable(id,name){
    instructionSetArchitecture = isa;
    nFlag = 0;
    vFlag = 0;
    zFlag = 0;
    cFlag = 0;
    executedInstructions = 0;
    jumpInstructions;
    aluInstructions;
    memoryInstructions;
} 

/* Access methods */
ISA* Processor::getISA(){
    return instructionSetArchitecture;
}

unsigned long Processor::getPCValue(){
    return PC;
}

void Processor::finishedExecution(){
    compSystem->markProcessorAsFinished();
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

void Processor::setISA(ISA* isa){
    this->instructionSetArchitecture = isa;
    this->architectedRegisterFile = isa->createArchitectedRegisterFile();
}

void Processor::setComputationalSystem(ComputationalSystem* compSys){
    this->compSystem = compSys;
}

FetchStage* Processor::getFetchStage(){
    return fetchStage;
}

ExecuteStage* Processor::getExecuteStage(){
    return executeStage;
}
    
void Processor::printStatistics(ofstream* file){
    ISimulable::printStatistics(file);
    *file << "Processor total executed instructions:        " << executedInstructions << endl;
    *file << "Processor total executed jump instructions:   " << jumpInstructions << endl;
    *file << "Processor total executed alu instructions:    " << aluInstructions << endl;
    *file << "Processor total executed memory instrucitons: " << memoryInstructions << endl;
}


