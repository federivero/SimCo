/* 
 * File:   MemoryResponse.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:56 PM
 */

#ifndef MEMORYRESPONSE_H
#define	MEMORYRESPONSE_H

#include "../interconnect/Message.h"
#include "MemoryRequest.h"
#include "MemoryChunk.h"

class MemoryRequest;

class MemoryResponse : public Message{
        private:
            unsigned int adress;
            MemoryChunk* rawData;
            
            // Pointer to the request which originated this response
            MemoryRequest* request;
        public:
            MemoryResponse(unsigned int adr, MessageType type, MemoryRequest*);
            // Getters
            MemoryChunk* getRawData();
            unsigned int getMemoryAdress();
            MemoryRequest* getMemoryRequest();
            // Setters
            void setRawData(MemoryChunk* chunk);
};

// When a memory device provides an overriding memory request, it sends an InvalidateMemoryResponse, no 
// signalize to other devices that they should abort the corresponding Memory Request
class InvalidatingMemoryResponse : public MemoryResponse{
    private:
    
    public:
        InvalidatingMemoryResponse(unsigned int addr, MessageType type, MemoryRequest* request);
};

#endif	/* MEMORYRESPONSE_H */

