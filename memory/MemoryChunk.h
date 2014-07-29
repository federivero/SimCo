/* 
 * File:   MemoryChunk.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 02:19 PM
 */

#ifndef MEMORYCHUNK_H
#define	MEMORYCHUNK_H

#include <iostream>
#include "../exceptions/RuntimeException.h"

using namespace std;

/* Simple data type to represent variable length memory chunks */
class MemoryChunk{
private:
    unsigned char* bytes;
    unsigned int bytesLength;
public:
    MemoryChunk(unsigned char* data, unsigned int dataLength):bytes(data),bytesLength(dataLength){};
    unsigned char* getBytes(){ return bytes; };
    unsigned int getBytesLength(){ return bytesLength; };
    void copyTo(unsigned char* copyBuffer){
        for (int j = 0; j < bytesLength; j++){
            copyBuffer[j] = bytes[j];
        }
    };
    void copyFrom(unsigned char* data){
        for (int j = 0; j < bytesLength; j++){
            bytes[j] = data[j];
        }
    };
    void addChunk(MemoryChunk* other){
        int i = 0;
        unsigned char* aux = bytes;
        bytes = new unsigned char[bytesLength + other->getBytesLength()];
        for (; i < bytesLength; i++){
            bytes[i] = aux[i];
        }
        other->copyTo(&bytes[i]);
        delete aux;
        bytesLength += other->getBytesLength();
    }
    
    // PRE: size <= 4
    int asInt(bool littleEndian){
        if (this->bytesLength > 4){
            throw new RuntimeException("Bad use of MemoryChunk function 'asInt', byteLength greater than 4");
        }
        int result = 0;
        if (littleEndian){
            for (int i = bytesLength - 1; i > 0; i--){
                result = (result << 8) | bytes[i];
            }
        }else{
            for (int i = 0; i < bytesLength; i++){
                result = (result << 8) | bytes[i];
            }
        }
    }
    // PRE:
    static MemoryChunk* fromInt(unsigned long value, int chunkLength, bool littleEndian){
        unsigned char* rawData = new unsigned char[chunkLength];
        if (littleEndian){
            for (int i = 0; i < chunkLength; i++){
                unsigned char pos = (value & 255); // keep last 8 bits 
                rawData[i] = pos;
                value = value >> 8;
            }
        }else{
            // TODO
            
        }
        return new MemoryChunk(rawData,chunkLength);
    }
    
    // Debug 
    void print(){
        for (int i = 0; i < bytesLength; i++){
            cout << bytes[i];
        }
        cout << endl;
    }
};


#endif	/* MEMORYCHUNK_H */

