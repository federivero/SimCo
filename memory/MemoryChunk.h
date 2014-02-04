/* 
 * File:   MemoryChunk.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 02:19 PM
 */

#ifndef MEMORYCHUNK_H
#define	MEMORYCHUNK_H

/* Simple data type to represent variable length memory chunks */
class MemoryChunk{
private:
    unsigned char* bytes;
    unsigned int bytesLength;
public:
    MemoryChunk(unsigned char* data, unsigned int dataLength):bytes(data),bytesLength(dataLength){};
    unsigned char* getBytes(){ return bytes; };
    unsigned int getBytesLength(){ return bytesLength; };
};


#endif	/* MEMORYCHUNK_H */

