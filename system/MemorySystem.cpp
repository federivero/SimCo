
#include "MemorySystem.h"
#include "../simulator/ConfigManager.h"

#include <sys/mman.h>

MemorySystem::MemorySystem(ComputationalSystem* compSys):compSystem(compSys){
    distributedMemory = ConfigManager::getInstance()->getBoolParameter(DISTRIBUTED_MEMORY);
    memoryDeviceCount = ConfigManager::getInstance()->getIntParameter(DIST_MEMORY_DEVICE_COUNT);
    globalMemoryMap = new MemoryMapEntry*[memoryDeviceCount];
    /* for the moment, there's only one device of DRAM */
    globalMemoryMap[0] = new MemoryMapEntry();
    
}

void MemorySystem::setMemoryContent(MemoryChunk* content, MemoryAddress* initialAdress){
    /* First, check which of the Memory Devices holds desired adress */
    bool found = false;
    int searchDeviceNumber = memoryDeviceCount / 2;
    unsigned long targetAdress = initialAdress->toGlobalAddress();
    while (!found){
        /* BinarySearch*/
        MemoryMapEntry* search = globalMemoryMap[searchDeviceNumber];
        if (targetAdress < search->getInitialAdress()){
            
        }else if (targetAdress > search->getEndAdress()){
            /* TODO: Check for memory allignment issues*/
            
        }else{
            /* This is the current entry! */
            search->getMemoryDevice()->setMemoryContent(content, initialAdress);
        }
    }
}





