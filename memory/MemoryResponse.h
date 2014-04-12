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

#endif	/* MEMORYRESPONSE_H */

