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

class PipelineStage;

class Instruction{
private:
    /* Reference to instruction archetype*/
    StaticInstruction* archetype;
    
    /* Reference to the pipeline Stage where the instruction is atm */
    PipelineStage* pipeStage;
    
    /* Binary codification of instruction */
    MemoryChunk* rawInstruction;
    
    /* Decoded info */
    unsigned short sourceRegisterOne;
    unsigned short sourceRegisterTwo;
    unsigned short destinationRegister;
    unsigned short instructionOpcode;
    unsigned int immediate;
    
    /* MIPS32 specific -> TODO: think of a class hierarchy tree for this: 
                                more clear and without useless information? */
    unsigned int shiftAmmount;
    /* For ALU instructions, the ALU fucntion to perform */
    unsigned char function;
public:
    Instruction();
    void setArchetype(StaticInstruction* archetype);
    StaticInstruction* getArchetype();
    unsigned short getSourceRegisterOne();
    unsigned short getSourceRegisterTwo();
    unsigned short getDestinationRegister();
    unsigned short getInstructionOpcode();
    unsigned short getShiftAmmount();
    unsigned char getFunction();
    unsigned int getImmediate();
    MemoryChunk* getRawInstruction();
    void setSourceRegisterOne(unsigned short value);
    void setSourceRegisterTwo(unsigned short value);
    void setDestinationRegister(unsigned short value);
    void setInstructionOpcode(unsigned short value);
    void setRawInstruction(MemoryChunk* value);
    void setShiftAmmount(unsigned int value);
    void setFunction(unsigned char value);
    void setImmediate(unsigned int value);
};

#endif	/* INSTRUCTION_H */

