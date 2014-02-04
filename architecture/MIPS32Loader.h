/* 
 * File:   MIPS32Loader.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 05:34 PM
 */

#ifndef MIPS32LOADER_H
#define	MIPS32LOADER_H

#include "../system/MemorySystem.h"
#include "../memory/MemoryAddress.h"
#include "Loader.h"

class MIPS32Loader : public Loader{
    private:
        
    public:   
        MIPS32Loader(MemorySystem* memSystem);
        void loadProgram(char* fileName, MemoryAddress* initialAdress);
};

#endif	/* MIPS32LOADER_H */

