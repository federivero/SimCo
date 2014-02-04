/* 
 * File:   MemoryResponse.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:56 PM
 */

#ifndef MEMORYRESPONSE_H
#define	MEMORYRESPONSE_H

#include "Message.h"
#include "MemoryChunk.h"

class MemoryResponse : public Message{
        private:
            unsigned int adress;
            MemoryChunk* rawData;
        public:
            MemoryResponse(unsigned int adr);
            MemoryChunk* getRawData();
};

#endif	/* MEMORYRESPONSE_H */

