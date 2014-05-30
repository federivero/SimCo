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

enum ALUFunction{
    ALU_FUNCTION_INT_ADD,       // Unsigned add
    ALU_FUNCTION_INT_SUB,       // Unsigned sub
    ALU_FUNCTION_SHIFT_RIGHT,   // Shift Right
    ALU_FUNCTION_SHIFT_LEFT,    // Shift Left
    ALU_FUNCTION_AND,           // Binary And
    ALU_FUNCTION_OR,            // Binary OR
    ALU_FUNCTION_XOR,           // Binary XOR
    ALU_FUNCTION_MOV,           // Copy instruction
    ALU_FUNCTION_INT_MUL,       // Integer Multiplication
    ALU_FUNCTION_INT_DIV        // Integer Division
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
    
    virtual Operand* getOperand(int operandNumber);
    virtual Operand* getDestinationOperand();
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
        Operand* getOperand(int operandNumber);
        Operand* getDestinationOperand();
        void setOperand(Operand* oper, int operandNumber);
        void setInstructionResult(InstructionResult* result);
};




#endif	/* INSTRUCTION_H */

