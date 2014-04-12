
#include "MemorySystem.h"
#include "../simulator/ConfigManager.h"
#include "../memory/MemoryDevice.h"

#include <sys/mman.h>           

MemorySystem::MemorySystem(ComputationalSystem* compSys, int deviceCount, int distributedMemoryDeviceCount):compSystem(compSys){
    globalMemoryMap = new MemoryMapEntry*[distributedMemoryDeviceCount];
    /* for the moment, there's only one device of DRAM */
    globalMemoryMap[0] = new MemoryMapEntry();
    
    memoryDeviceCount = deviceCount;
    devices = new MemoryDevice*[memoryDeviceCount];
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
            search->getMemoryDevice()->setMemoryContent(content, initialAdress->toGlobalAddress());
        }
    }
}

void MemorySystem::addMemoryDevice(MemoryDevice* device, int position){
    devices[position] = device;
}

MemoryDevice** MemorySystem::getDevices(){
    return devices;
}

int MemorySystem::getMemoryDeviceCount(){
    return memoryDeviceCount;
}

