
#include "MemoryResponse.h"
#include "MemoryRequest.h"

MemoryResponse::MemoryResponse(unsigned int adr, MessageType type, MemoryRequest* mreq)
        :adress(adr),
        Message(type),
        request(mreq){
    
}

MemoryChunk* MemoryResponse::getRawData(){
    return rawData;
}

MemoryRequest* MemoryResponse::getMemoryRequest(){
    return request;
}

unsigned int MemoryResponse::getMemoryAdress(){
    return adress;
}

void MemoryResponse::setRawData(MemoryChunk* chunk){
    rawData = chunk;
}

/* Invalidate Memory Response */

InvalidatingMemoryResponse::InvalidatingMemoryResponse(unsigned int addr, MessageType type, MemoryRequest* request):MemoryResponse(addr,type,request)
{
    
}


