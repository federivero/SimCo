/* 
 * File:   ISA.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 07:01 PM
 */

#ifndef ISA_H
#define	ISA_H

#include "Instruction.h"
#include "../memory/MemoryChunk.h"

class Instruction;

class ISA{
private:
public:
    virtual Instruction* buildInstruction(char* opcode, char** operands, int operandsLength) = 0;
    virtual Instruction* decodeInstruction(MemoryChunk*) = 0;
    virtual MemoryChunk* encodeInstruction(Instruction* inst) = 0;
};

#endif	/* ISA_H */

