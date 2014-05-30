
#include "Instruction.h"
#include "../exceptions/RuntimeException.h"

Instruction::Instruction(){
    
}

StaticInstruction* Instruction::getArchetype(){
    return archetype;
}

Operand* Instruction::getOperand(int operandNumber){
    // TODO: This instruction has to be pure virtual when all implementations of instruction are implemented
    return NULL;
}
void Instruction::setOperand(Operand* operand, int operandNumber){
    // TODO: This instruction has to be pure virtual when all implementations of instruction are implemented
}
void Instruction::setInstructionResult(InstructionResult* result){
    // TODO: This instruction has to be pure virtual when all implementations of instruction are implemented
}
Operand* Instruction::getDestinationOperand(){
    // TODO: This instruction has to be pure virtual whenn all implementations of instructions are implemented
}

unsigned short Instruction::getInstructionOpcode(){
    return instructionOpcode;
}

MemoryChunk* Instruction::getRawInstruction(){
    return rawInstruction;
}

void Instruction::setArchetype(StaticInstruction* arche){
    archetype = arche;
}

void Instruction::setInstructionOpcode(unsigned short value){
    instructionOpcode = value;
}

void Instruction::setRawInstruction(MemoryChunk* value){
    rawInstruction = value;
}

InstructionResult* Instruction::getInstructionResult(){
    return instructionResult;
}

/* ALUInstruction Instructions */

ALUInstruction::ALUInstruction(int operandCount, ALUFunction function){
    this->function = function;
    this->operands = new Operand*[operandCount];
    for (int i = 0; i < operandCount; i++){
        this->operands[i] = NULL;
    }
}

ALUFunction ALUInstruction::getALUFunction(){
    return function;
}

Operand* ALUInstruction::getOperand(int operandNumber){
    return this->operands[operandNumber];
}

void ALUInstruction::setOperand(Operand* oper, int operandNumber){
    this->operands[operandNumber] = oper;
}

void ALUInstruction::setInstructionResult(InstructionResult* result){
    if (result->getType() != INSTRUCTION_RESULT_INT){
        throw new RuntimeException((char*)"Error: instruction result for ALUInstruction should be INT");
    }
    this->instructionResult = result;
}

Operand* ALUInstruction::getDestinationOperand(){
    // Destination operand is the last of the array
    return operands[archetype->getOperandCount()-1];
}
    


