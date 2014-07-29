
#include "MemoryRequest.h"

MemoryRequest::MemoryRequest(unsigned int adr, unsigned int size, MessageType type, unsigned long originDeviceId):       
        address(adr),
        requestSize(size),
        Message(type,originDeviceId)
{ }

MemoryChunk* MemoryRequest::getRawData(){
    return rawData;
}

unsigned int MemoryRequest::getMemoryAddress(){
    return address;
}

unsigned int MemoryRequest::getRequestSize(){
    return requestSize;
}

void MemoryRequest::setRawData(MemoryChunk* data){
    rawData = data;
}

void MemoryRequest::setOriginalRequest(MemoryRequest* req){
    originalRequest = req;
}

MemoryRequest* MemoryRequest::getOriginalRequest(){
    return originalRequest;
}

