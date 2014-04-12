/* 
 * File:   MemoryChunk.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 02:19 PM
 */

#ifndef MEMORYCHUNK_H
#define	MEMORYCHUNK_H

#include <iostream>

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
    
    // Debug 
    void print(){
        for (int i = 0; i < bytesLength; i++){
            cout << bytes[i];
        }
        cout << endl;
    }
};


#endif	/* MEMORYCHUNK_H */

