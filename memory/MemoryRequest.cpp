
#include "MemoryRequest.h"

MemoryRequest::MemoryRequest(unsigned int adr):adress(adr){
    
}

MemoryChunk* MemoryRequest::getRawData(){
    return rawData;
}


