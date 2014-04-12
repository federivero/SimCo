/* 
 * File:   MemoryRequest.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 03:52 PM
 */

#ifndef MEMORYREQUEST_H
#define	MEMORYREQUEST_H

#include "../interconnect/Message.h"
#include "MemoryChunk.h"

class MemoryRequest : public Message{
    /* Class For memory read - write request Meessages */
    private:
        unsigned int adress;
        // Number of bytes requested
        unsigned int requestSize;
        MemoryChunk* rawData;
        
        // Pointer to the  request which originated this object 
        // e.g: Cache misses generate new memory requests, which asks for 
        // an entire memory block
        MemoryRequest* originalRequest;
    public:
        MemoryRequest(unsigned int adress, unsigned int size, MessageType type);
        MemoryChunk* getRawData();
        unsigned int getMemoryAdress();
        unsigned int getRequestSize();
        void setRawData(MemoryChunk* data);
        MemoryRequest* getOriginalRequest();
        void setOriginalRequest(MemoryRequest* req);
};

#endif	/* MEMORYREQUEST_H */

