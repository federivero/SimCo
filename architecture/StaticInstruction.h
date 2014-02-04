/* 
 * File:   StaticInstruction.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:40 AM
 */

#ifndef STATICINSTRUCTION_H
#define	STATICINSTRUCTION_H

enum InstructionType{
    NOP, INT_ALU, FP_ALU, JUMP_BRANCH, LOAD_STORE, READ_MODIFY_WRITE
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

