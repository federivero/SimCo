
#include "MemoryMapEntry.h"

MemoryMapEntry::MemoryMapEntry(){
    
}

unsigned long MemoryMapEntry::getInitialAdress(){
    return initialAdress;
}

unsigned long MemoryMapEntry::getEndAdress(){
    return endAdress;
}

MemoryDevice* MemoryMapEntry::getMemoryDevice(){
    return device;
}

void MemoryMapEntry::setInitialAdress(unsigned long adress){
    initialAdress = adress;
}

void MemoryMapEntry::setEndAdress(unsigned long adress){
    endAdress = adress;
}

void MemoryMapEntry::setMemoryDevice(MemoryDevice* mDevice){
    device = mDevice;
}
