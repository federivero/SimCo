
#include "StaticInstruction.h"

StaticInstruction::StaticInstruction(int sourceOperCount, int destOperandCount, InstructionType type):sourceOperandCount(sourceOperCount),destinationOperandCount(destOperandCount), instType(type){
    
}

int StaticInstruction::getSourceOperandCount(){
    return sourceOperandCount;
}

int StaticInstruction::getDestinationOperandCounts(){
    return destinationOperandCount;
}

InstructionType StaticInstruction::getInstructionType(){
    return instType;
}







