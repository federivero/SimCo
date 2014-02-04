/* 
 * File:   MemoryRequest.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:52 PM
 */

#ifndef MEMORYREQUEST_H
#define	MEMORYREQUEST_H

#include "Message.h"
#include "MemoryChunk.h"

class MemoryRequest : public Message{
    private:
        unsigned int adress;
        MemoryChunk* rawData;
    public:
        MemoryRequest(unsigned int adress);
        MemoryChunk* getRawData();
};

#endif	/* MEMORYREQUEST_H */

