
#include "MemoryMapEntry.h"

MemoryMapEntry::MemoryMapEntry(){
    
}

unsigned long MemoryMapEntry::getInitialAddress(){
    return initialAddress;
}

unsigned long MemoryMapEntry::getEndAddress(){
    return endAddress;
}

MemoryDevice* MemoryMapEntry::getMemoryDevice(){
    return device;
}

void MemoryMapEntry::setInitialAddress(unsigned long address){
    initialAddress = address;
}

void MemoryMapEntry::setEndAddress(unsigned long address){
    endAddress = address;
}

void MemoryMapEntry::setMemoryDevice(MemoryDevice* mDevice){
    device = mDevice;
}
