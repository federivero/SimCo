
#include "MemoryRequest.h"

MemoryRequest::MemoryRequest(unsigned int adr, unsigned int size, MessageType type):       
        adress(adr),
        requestSize(size),
        Message(type)
{ }

MemoryChunk* MemoryRequest::getRawData(){
    return rawData;
}

unsigned int MemoryRequest::getMemoryAdress(){
    return adress;
}

unsigned int MemoryRequest::getRequestSize(){
    return requestSize;
}

void MemoryRequest::setRawData(MemoryChunk* data){
    rawData = data;
}

MemoryRequest* MemoryRequest::getOriginalRequest(){
    return originalRequest;
}

