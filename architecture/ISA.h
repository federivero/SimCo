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

class RegisterFile;
class Instruction;
class Loader;

enum ISAType{
    ISA_MIPS_32, ISA_TYPE_UNDEFINED
};

class ISA{
private:
protected:
    Loader* loader; 
public:
    // Returns the binary representation of the instruction
    virtual MemoryChunk* buildInstruction(char* opcode, char** operands, int operandsLength) = 0;
    // Given a binary representation of an instruction, returns the SimCo
    // Instruction Model of the instruction
    virtual Instruction* decodeInstruction(MemoryChunk*) = 0;
    // Returns the binary representation of the SimCo instruction 'inst'
    virtual MemoryChunk* encodeInstruction(Instruction* inst) = 0;
    /* Creates a data structure with the Architected Register File */
    virtual RegisterFile* createArchitectedRegisterFile() = 0;
    // Returns true if ISA is little endian
    virtual bool isLittleEndian() = 0;
    /* ISA basic information */ 
    virtual int getInstructionLength() = 0;
    
    // Sets the specific instance of the loader
    void setLoader(Loader* loader){
        this->loader = loader;
    }
};

#endif	/* ISA_H */

