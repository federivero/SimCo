
#include "../exceptions/RuntimeException.h"
#include "Instruction.h"
#include "Operand.h"

Instruction::Instruction(){
    
}

StaticInstruction* Instruction::getArchetype(){
    return archetype;
}

Operand* Instruction::getSourceOperand(int operandNumber){
    // TODO: This instruction has to be pure virtual when all implementations of instruction are implemented
    return NULL;
}
void Instruction::setOperand(Operand* operand, int operandNumber){
    // TODO: This instruction has to be pure virtual when all implementations of instruction are implemented
}
void Instruction::setInstructionResult(InstructionResult* result){
    this->instructionResult = result;
}

Operand* Instruction::getDestinationOperand(int operandCount){
    // TODO: This instruction has to be pure virtual whenn all implementations of instructions are implemented
    return NULL;
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

/* ALUInstruction operations */

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

Operand* ALUInstruction::getSourceOperand(int operandNumber){
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

Operand* ALUInstruction::getDestinationOperand(int operandNumber){
    // Destination operand is the last of the array
    return operands[archetype->getSourceOperandCount()];
}
    
/* JumpInstruction operations*/

JumpInstruction::JumpInstruction(){
    
}

Operand* JumpInstruction::getDestinationOperand(int operandNumber){
    return destinationOperand;
}

void JumpInstruction::setOperand(Operand* oper, int operandNumber){
    // Just one operand, assume its 1
    if (operandNumber == 0){
        this->pcValueOperand = oper;
    }else{
        this->destinationOperand = oper;
    }
}

Operand* JumpInstruction::getSourceOperand(int operandNumber){
    if (operandNumber == 0){
        return pcValueOperand;
    }else{
        return destinationOperand;
    }
}

// BranchInstruction

BranchInstruction::BranchInstruction(){
    this->destinationOperand = new SpecialRegisterOperand(SPECIAL_REGISTER_PC);
}

Operand* BranchInstruction::getSourceOperand(int operandNumber){
    if (operandNumber == 0){
        return firstComparator;
    }else if (operandNumber == 1){
        return secondComparator;
    }else if (operandNumber == 2){
        return pcValueTakenOperand;
    }else if (operandNumber == 3){
        return pcValueNotTakenOperand;
    }
}

Operand* BranchInstruction::getDestinationOperand(int operandNumber){
    if (operandNumber == 0){
        return destinationOperand;
    }else{
        throw new RuntimeException("Runtime error: trying to get second destination operand of a BranchInstruction");
    }
}

void BranchInstruction::setDestinationOperand(int destinationOperandNumber, Operand* operand){
    if (destinationOperandNumber == 0){
        destinationOperand = operand;
    }else{
        throw new RuntimeException("Runtime error: trying to set second destination operand of a BranchInstruction");
    }
}
ConditionType BranchInstruction::getConditionType(){
    return conditionType;
}

void BranchInstruction::setConditionType(ConditionType type){
    this->conditionType = type;
}
    
void BranchInstruction::setFirstComparator(Operand* comparator){
    this->firstComparator = comparator;
}

void BranchInstruction::setSecondComparator(Operand* comparator){
    this->secondComparator = comparator;
}

void BranchInstruction::setPCValueTakenOperand(Operand* operand){
    this->pcValueTakenOperand = operand;
}

void BranchInstruction::setPCValueNotTakenOperand(Operand* operand){
    this->pcValueNotTakenOperand = operand;
}

void BranchInstruction::setInstructionResult(InstructionResult* result){
    if (result->getType() != INSTRUCTION_RESULT_INT){
        throw new RuntimeException("Non integer result being set to Branch Instruction");
    }
    InstructionResultInt* instResultInt = (InstructionResultInt*) result;
    if (instResultInt->getResult() == 0){
        // Branch not taken
        instResultInt->setResult(pcValueNotTakenOperand->getOperandBinaryValue());
    }else{
        // Branch taken
        instResultInt->setResult(pcValueTakenOperand->getOperandBinaryValue());
    }
    instructionResult = result;
}

// LoadStoreInstruction 

LoadStoreInstruction::LoadStoreInstruction(MessageType loadStore, int loadStoreSize){
    this->loadStore = loadStore;
    this->loadStoreSize = loadStoreSize;
}

MessageType LoadStoreInstruction::getLoadStoreType(){
    return loadStore;
}

int LoadStoreInstruction::getLoadStoreSize(){
    return loadStoreSize;
}
        
        
Operand* LoadStoreInstruction::getAddressOperand(){
    return this->addressOperand;
}

Operand* LoadStoreInstruction::getReadWriteOperand(){
    return this->readWriteOperand;
}

void LoadStoreInstruction::setAddressOperand(Operand* operand){
    this->addressOperand = operand;
}

void LoadStoreInstruction::setReadWriteOperand(Operand* operand){
    this->readWriteOperand = operand;
}

Operand* LoadStoreInstruction::getDestinationOperand(int operandNumber){
    // If its a load, destination operand its the register, if its a write, destination operand its a memory address
    if (loadStore == MEMORY_REQUEST_MEMORY_READ){
        return readWriteOperand;
    }else if (loadStore == MEMORY_REQUEST_MEMORY_WRITE){
        return addressOperand;
    }else{
        return NULL;
    }
}

Operand* LoadStoreInstruction::getSourceOperand(int operandNumber){
    if (operandNumber > 1){
        throw new RuntimeException("Only one source opernand for load store instructions");
    }else{
        if (operandNumber == 0){
            if (loadStore == MEMORY_REQUEST_MEMORY_READ){
                return addressOperand;
            }else if (loadStore == MEMORY_REQUEST_MEMORY_WRITE){
                return readWriteOperand;
            }else{
                return NULL;
            }
        }else if (operandNumber == 1){
            if (loadStore == MEMORY_REQUEST_MEMORY_WRITE){
                return addressOperand;
            }
        }
    }
}


