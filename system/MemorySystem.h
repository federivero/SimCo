/* 
 * File:   MemorySystem.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:50 AM
 */

#ifndef MEMORYSYSTEM_H
#define	MEMORYSYSTEM_H

#include "ComputationalSystem.h"
#include "../memory/MemoryAddress.h"
#include "../memory/MemoryChunk.h"
#include "MemoryMapEntry.h"

class ComputationalSystem;
class MemoryMapEntry;

class MemorySystem{
    private:
        ComputationalSystem*     compSystem;
        bool uniformMemoryAccess;
        
        /* GlobalMemoryMap, used if we are using distributed memory 
         * in that case, we have to keep track of which device holds every 
         * adress */
        bool distributedMemory;
        MemoryMapEntry** globalMemoryMap;
        int memoryDeviceCount;
    public:
        MemorySystem(ComputationalSystem* compSystem);
        void setMemoryContent(MemoryChunk* content, MemoryAddress* initialAdress);
};

#endif	/* MEMORYSYSTEM_H */

