/* 
 * File:   Loader.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 05:06 PM
 */

#ifndef LOADER_H
#define	LOADER_H

#include "../memory/MemoryAddress.h"
#include "../system/MemorySystem.h"
#include "ISA.h"

/* Class in charge to parse the program file, and load it into memory. This
 * job includes encoding instruction to binary and passing them to the memory
 * controller */
class Loader{
  
private:
protected:
    MemorySystem* memorySystem;
    ISA* instructionSetArchitecture;
public:
    Loader(MemorySystem*, ISA*);
    virtual void loadProgram(char* fileName, MemoryAddress* initialAdress) = 0;
};

#endif	/* LOADER_H */

