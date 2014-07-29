/* 
 * File:   Instruction.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:01 AM
 */

#ifndef INSTRUCTION_H
#define	INSTRUCTION_H

#include "StaticInstruction.h"
#include "../memory/MemoryChunk.h"
#include "../interconnect/Message.h"

enum ALUFunction{
    ALU_FUNCTION_INT_ADD,               // Signed add
    ALU_FUNCTION_INT_ADD_UNSIGNED,      // Unsigned add
    ALU_FUNCTION_INT_SUB,               // Signed sub
    ALU_FUNCTION_INT_SUB_UNSIGNED,      // Unsigned sub
    ALU_FUNCTION_SHIFT_RIGHT_LOGICAL,   // Shift Right Logical
    ALU_FUNCTION_SHIFT_RIGHT_ARITHMETIC,// Shift Right Arithmetic
    ALU_FUNCTION_SHIFT_LEFT,            // Shift Left
    ALU_FUNCTION_AND,                   // Binary And
    ALU_FUNCTION_OR,                    // Binary OR
    ALU_FUNCTION_XOR,                   // Binary XOR
    ALU_FUNCTION_NOR,                   // Binary NOR
    ALU_FUNCTION_MOV,                   // Copy instruction
    ALU_FUNCTION_INT_MUL,               // Integer Multiplication
    ALU_FUNCTION_INT_DIV,               // Integer Division
    ALU_FUNCTION_MOV_UPPER_16_BITS,     // Set the upper 16 bits of the register
    ALU_FUNCTION_MOV_LOWER_16_BITS      // Set the lower 16 bits of the register
};

enum InstructionResultType{
    INSTRUCTION_RESULT_INT,
    INSTRUCTION_RESULT_FP
};

class Operand;
class InstructionResult;

class Instruction{
private:
    /* Binary codification of instruction */
    MemoryChunk* rawInstruction;
    
    unsigned short instructionOpcode;
protected:
    /* Reference to instruction archetype*/
    StaticInstruction* archetype;
    
    // Data structure holding instruction result
    InstructionResult* instructionResult;
public:
    Instruction();
    void setArchetype(StaticInstruction* archetype);
    StaticInstruction* getArchetype();
    
    virtual Operand* getSourceOperand(int operandNumber);
    virtual Operand* getDestinationOperand(int operandNumber);
    virtual void setOperand(Operand* operand, int operandNumber);
    
    // Access Methods
    virtual void setInstructionResult(InstructionResult* result);
    InstructionResult* getInstructionResult();
    unsigned short getInstructionOpcode();
    void setInstructionOpcode(unsigned short value);
    MemoryChunk* getRawInstruction();
    void setRawInstruction(MemoryChunk* value);
};

/* Generic class to map instruction results */
class InstructionResult{
    private:
        InstructionResultType type;
    public:    
        InstructionResult(InstructionResultType instType):type(instType){};
        InstructionResultType getType(){
            return type;
        };
};

// int result -> Used for int operations of 32 bit architectures
class InstructionResultInt : public InstructionResult{
    private:
        int result;
    public:
        InstructionResultInt(int instructionResult)
                :InstructionResult(INSTRUCTION_RESULT_INT)
                ,result(instructionResult){};
        int getResult(){
            return result;
        }
};

// fp result -> Used for FP operations of 32 bit architectures
class InstructionResultFP : public InstructionResult{
    private:
        float result;
    public:
        InstructionResultFP(float instructionResult)
                :InstructionResult(INSTRUCTION_RESULT_FP)
                ,result(instructionResult){};
        float getResult(){
            return result;
        }
};

class ALUInstruction: public Instruction{
    private:
        Operand** operands;
        ALUFunction function;
    public:
        ALUInstruction(int operandCount, ALUFunction function);
        ALUFunction getALUFunction();
        Operand* getSourceOperand(int operandNumber);
        Operand* getDestinationOperand(int operandNumber);
        void setOperand(Operand* oper, int operandNumber);
        void setInstructionResult(InstructionResult* result);
};

class JumpInstruction : public Instruction{
    private:
        Operand* pcValueOperand;
        Operand* destinationOperand;
        
    public:
        JumpInstruction();
        Operand* getSourceOperand(int operandNumber);
        Operand* getDestinationOperand(int operandNumber);
        void setOperand(Operand* oper, int operandNumber);
};

class LoadStoreInstruction : public Instruction{
    private:
        MessageType loadStore; // load or store operation
        int loadStoreSize; // Size of the read or write in bytes
        Operand* addressOperand; 
        Operand* readWriteOperand;
    public:
        LoadStoreInstruction(MessageType loadStore, int loadStoreSize);
        Operand* getAddressOperand();
        Operand* getReadWriteOperand();
        MessageType getLoadStoreType();
        int getLoadStoreSize();
        void setAddressOperand(Operand* operand);
        void setReadWriteOperand(Operand* operand);
        Operand* getDestinationOperand(int opernandNumber);
        Operand* getSourceOperand(int operandNumber);
};



#endif	/* INSTRUCTION_H */

