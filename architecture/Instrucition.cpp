
#include "Instruction.h"

Instruction::Instruction(){
    
}

StaticInstruction* Instruction::getArchetype(){
    return archetype;
}

unsigned short Instruction::getDestinationRegister(){
    return destinationRegister;
}

unsigned short Instruction::getInstructionOpcode(){
    return instructionOpcode;
}

unsigned short Instruction::getSourceRegisterOne(){
    return sourceRegisterOne;
}

unsigned short Instruction::getSourceRegisterTwo(){
    return sourceRegisterTwo;
}

MemoryChunk* Instruction::getRawInstruction(){
    return rawInstruction;
}

void Instruction::setArchetype(StaticInstruction* arche){
    archetype = arche;
}

void Instruction::setDestinationRegister(unsigned short value){
    destinationRegister = value;
}

void Instruction::setInstructionOpcode(unsigned short value){
    instructionOpcode = value;
}

void Instruction::setSourceRegisterOne(unsigned short value){
    sourceRegisterOne = value;
}

void Instruction::setSourceRegisterTwo(unsigned short value){
    sourceRegisterTwo = value;
}

void Instruction::setRawInstruction(MemoryChunk* value){
    rawInstruction = value;
}

unsigned short Instruction::getShiftAmmount(){
    return shiftAmmount;
}

void Instruction::setShiftAmmount(unsigned int value){
    shiftAmmount = value;
}

void Instruction::setFunction(unsigned char value){
    function = value;
}

unsigned char Instruction::getFunction(){
    return function;
}

unsigned int Instruction::getImmediate(){
    return immediate;
}

void Instruction::setImmediate(unsigned int value){
    immediate = value;
}








