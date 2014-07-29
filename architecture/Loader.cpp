
#include "Loader.h"


Loader::Loader(MemorySystem* memSystem, ISA* isa):memorySystem(memSystem),instructionSetArchitecture(isa){
    tagMap = new ListMap<string,unsigned long>(1000);
}

unsigned long Loader::getTagValue(char* tag){
    string val = string(tag);
    return tagMap->getData(val);
}