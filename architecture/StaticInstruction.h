/* 
 * File:   StaticInstruction.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:40 AM
 */

#ifndef STATICINSTRUCTION_H
#define	STATICINSTRUCTION_H

enum InstructionType{
    INSTRUCTION_TYPE_NOP, INSTRUCTION_TYPE_INT_ALU, INSTRUCTION_TYPE_FP_ALU, 
    INSTRUCTION_TYPE_JUMP_BRANCH, INSTRUCTION_TYPE_LOAD_STORE, INSTRUCTION_TYPE_READ_MODIFY_WRITE,
    INSTRUCTION_TYPE_SYSCALL // Used to end execution
};

class StaticInstruction{
private: 
    int operandCount;
    InstructionType instType;
public:
    StaticInstruction(int operCount, InstructionType type);
    int getOperandCount();
    InstructionType getInstructionType();
};

#endif	/* STATICINSTRUCTION_H */

