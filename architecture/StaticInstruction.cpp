
#include "StaticInstruction.h"

StaticInstruction::StaticInstruction(int operCount, InstructionType type):operandCount(operCount),instType(type){
    
}

int StaticInstruction::getOperandCount(){
    return operandCount;
}

InstructionType StaticInstruction::getInstructionType(){
    return instType;
}







