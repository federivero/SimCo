
#include "MemorySystem.h"
#include "../simulator/ConfigManager.h"
#include "../memory/MemoryDevice.h"
#include "../memory/RAM.h"

MemorySystem::MemorySystem(ComputationalSystem* compSys, int deviceCount, int distributedMemoryDeviceCount):compSystem(compSys){
    globalMemoryMap = new MemoryMapEntry*[distributedMemoryDeviceCount];
    /* for the moment, there's only one device of DRAM */
    globalMemoryMap[0] = new MemoryMapEntry();
    
    memoryDeviceCount = deviceCount;
    devices = new MemoryDevice*[memoryDeviceCount];
}

void MemorySystem::setMemoryContent(MemoryChunk* content, unsigned long initialAddress){
    globalMemoryMap[0]->getMemoryDevice()->setMemoryContent(content,initialAddress);
    // First, check which of the Memory Devices holds desired address 
    /* TODO: support NUMA
    bool found = false;
    int searchDeviceNumber = memoryDeviceCount / 2;
    unsigned long targetAddress = initialAddress;//->toGlobalAddress();
    while (!found){
        // BinarySearch
        MemoryMapEntry* search = globalMemoryMap[searchDeviceNumber];
        if (targetAddress < search->getInitialAddress()){
            
        }else if (targetAddress > search->getEndAddress()){
            // TODO: Check for memory allignment issues
            
        }else{
            // This is the current entry! 
            search->getMemoryDevice()->setMemoryContent(content, initialAddress);
        }
    }
     */
}

void MemorySystem::addMemoryDevice(MemoryDevice* device, int position){
    RAM* ram;
    if ((ram = dynamic_cast<RAM*>(device)) != NULL){
        globalMemoryMap[0]->setInitialAddress(0);
        globalMemoryMap[0]->setEndAddress(ram->getCapacity()-1);
        globalMemoryMap[0]->setMemoryDevice(ram);
    }
    devices[position] = device;
}

MemoryDevice** MemorySystem::getDevices(){
    return devices;
}

int MemorySystem::getMemoryDeviceCount(){
    return memoryDeviceCount;
}

