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
    INSTRUCTION_TYPE_JUMP, INSTRUCTION_TYPE_LOAD_STORE, INSTRUCTION_TYPE_READ_MODIFY_WRITE,
    INSTRUCTION_TYPE_BRANCH,
    INSTRUCTION_TYPE_SYSCALL // Used to end execution
};

class StaticInstruction{
private: 
    int sourceOperandCount;      // Number of source opernads on instruction
    int destinationOperandCount; // Destination operand count (some instructions change values on multiple registers)
    InstructionType instType;
public:
    StaticInstruction(int sourcOperCount, int destinationOperandCount, InstructionType type);
    int getSourceOperandCount();
    int getDestinationOperandCounts();
    InstructionType getInstructionType();
};

#endif	/* STATICINSTRUCTION_H */

