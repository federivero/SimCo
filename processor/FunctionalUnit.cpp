#include "FunctionalUnit.h"
#include "ExecuteStage.h"

// ISimulable operations
void FunctionalUnit::initCycle(){
}

FunctionalUnit::FunctionalUnit(unsigned long id, char* name, FunctionalUnitType funcType, ExecuteStage* execStage, int latency)
        :ISimulable(id,name),type(funcType){
    this->latency = latency;
    this->executionStage = execStage;
}

FunctionalUnitType FunctionalUnit::getType(){
    return type;
}

void FunctionalUnit::initExecution(){
    // TODO: This function has to be pure virtual when all implementations of FunctionalUnit are implemented
}

void FunctionalUnit::endExecution(){
    // TODO: This function has to be pure virtual when all implementations of FunctionalUnit are implemented
}

InstructionResult* FunctionalUnit::getInstructionResult(){
    // TODO: This function has to be pure virtual when all implementations of FunctionalUnit are implemented
    return NULL;
}

bool FunctionalUnit::isALU(){
    // Overriden on ALU class to correct this
    return false;
}

/* ALU Operations*/
ALU::ALU(unsigned long id, char* name, FunctionalUnitType type, ExecuteStage* execStage, int latency)
        :FunctionalUnit(id,name,type,execStage,latency){
    
}

bool ALU::getZFlagValue(){
    return zFlag;
}

bool ALU::getNFlagValue(){
    return nFlag;
}

bool ALU::getCFlagValue(){
    return cFlag;
}

bool ALU::getVFlagValue(){
    return vFlag;
}
    
bool ALU::isALU(){
    return true;
}

/* IntALU Operations */

IntALU::IntALU(unsigned long id, char* name, ExecuteStage* execStage, int latency)
    :ALU(id,name,FUNCTIONAL_UNIT_INT_ALU,execStage,latency){
}

void IntALU::setALUFunction(ALUFunction function){
    this->function = function;
}

void IntALU::setFirstOperand(long operand){
    this->firstOperand = operand;
}

void IntALU::setSecondOperand(long operand){
    this->secondOperand = operand;
}

InstructionResult* IntALU::getInstructionResult(){
    return instructionResult;
}

void IntALU::initExecution(){
    // Calculate instruction result and schedule event to simulate instruction latency
    int result;
    
    switch(this->function){
        case ALU_FUNCTION_AND:
            result = firstOperand & secondOperand;
            break;
        case ALU_FUNCTION_INT_ADD:
            result = firstOperand + secondOperand;
            if (result < (firstOperand + secondOperand)){
                cFlag = 1;
            }
            break;
        case ALU_FUNCTION_INT_SUB:
            result = firstOperand - secondOperand;
            break;
        case ALU_FUNCTION_MOV:
            result = firstOperand;
            break;
        case ALU_FUNCTION_OR:
            result = firstOperand | secondOperand;
            break;
        case ALU_FUNCTION_XOR:
            result = firstOperand ^ secondOperand;
            break;
        case ALU_FUNCTION_SHIFT_LEFT:
            result = firstOperand >> secondOperand;
            break;
        case ALU_FUNCTION_SHIFT_RIGHT:
            result = firstOperand << secondOperand;
            if (result < (firstOperand << secondOperand)){
                cFlag = 1;
                vFlag = 1;
            }
            break;
        default:
            // TODO: Throw exception
            break;
    }
    if (result < 0){
        nFlag = 1;
    }
    if (result == 0){
        zFlag = 1;
    }
    
    // TODO: Object Pooling?
    // TODO: Think of an extended class hierarchy to support 32 and 64 bit architectures
    instructionResult = new InstructionResultInt(result);
    
    FunctionalUnitEvent* event = new FunctionalUnitEvent(FUNCTIONAL_UNIT_EXECUTION_END,this);
    this->simulator->addEvent(event,latency-1);
}

void IntALU::endExecution(){
    executionStage->finishedExecution(this);
}

/* FunctionalUnitEvent Operations */
FunctionalUnitEvent::FunctionalUnitEvent(EventName name, FunctionalUnit* funit):IEventCallback(name){
    this->functionalUnit = funit;
}

void FunctionalUnitEvent::simulate(){
    switch(eventName){
        case FUNCTIONAL_UNIT_EXECUTION_INIT:
            functionalUnit->initExecution();
            break;
        case FUNCTIONAL_UNIT_EXECUTION_END:
            functionalUnit->endExecution();
            break;
    }
}