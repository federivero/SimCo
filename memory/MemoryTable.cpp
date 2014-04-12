#include "MemoryTable.h"
#include "../common/CustomMacros.h"
#include "../exceptions/UnalignedMemoryAccessException.h"
#include "../exceptions/RuntimeException.h"

#include <iostream>

using namespace std;

MemoryTable::MemoryTable(unsigned long cap):capacity(cap)
{ }

MultilevelMemoryTable::MultilevelMemoryTable(unsigned long cap, int levels):MemoryTable(cap),levelCount(levels)
{    
}

MultilevelMemoryTable* MultilevelMemoryTable::createMultilevelMemoryTable(unsigned long capacity, int levels){
    if (levels == 1){
        return new BaseMultilevelMemoryTable(capacity,levels);
    }else{
        return new MiddleMultilevelMemoryTable(capacity,levels);
    }
    
}

/* BaseMultilevelMemoryTable operations  */

BaseMultilevelMemoryTable::BaseMultilevelMemoryTable(unsigned long capacity, int levels)
        :MultilevelMemoryTable(capacity,levels){
    if (levels != 1){
        throw new RuntimeException("Wrong algorithm for construction of multilevel memory tables");
    }
    unsigned char* data = new unsigned char[capacity];
    for (int j = 0; j < capacity; j++) data[j] = 0;
    dataArray = new MemoryChunk(data,capacity);
}

MemoryChunk* BaseMultilevelMemoryTable::getMemoryContent(unsigned int address, unsigned int size){
    if ((address + size) > capacity){
        throw new UnalignedMemoryAccessException("Reached end of memory table");
    }else{
        MemoryChunk* result = new MemoryChunk(new unsigned char[size],size);
        result->copyFrom(&dataArray->getBytes()[address]);
        return result;
    }
}

void BaseMultilevelMemoryTable::setMemoryContent(unsigned int address, MemoryChunk* data){
    if ((address + data->getBytesLength()) > capacity){
        throw new UnalignedMemoryAccessException("Reached end of memory table");
    }else{
        data->copyTo(&dataArray->getBytes()[address]);
    }
}

/* MiddleMultilevelMemoryTable instructions */

MiddleMultilevelMemoryTable::MiddleMultilevelMemoryTable(unsigned long capacity, int levels)
        :MultilevelMemoryTable(capacity,levels){
    if ((levels <= 1) || (!isPowerOf2(capacity))){
        throw new RuntimeException("Wrong algorithm for construction of multilevel memory tables");
    }
    log2cap = log2(capacity);
    int log2indexLength = log2cap / levelCount;
    indexLength = base2Exp(log2indexLength);
    lowerLevelCapacity = base2Exp(log2cap - log2indexLength);
    if (levels == 1){
        // Sons are leaves
        indexes = (MultilevelMemoryTable**) new BaseMultilevelMemoryTable*[indexLength];
    }else{
        // Sons are inner nodes
        indexes = (MultilevelMemoryTable**) new MiddleMultilevelMemoryTable*[indexLength];
    }
    for (int i = 0; i < indexLength; i++){
        indexes[i] = NULL;
    }
}

MemoryChunk* MiddleMultilevelMemoryTable::getMemoryContent(unsigned int address, unsigned int size){
    if ((address + size) > capacity){
        throw new UnalignedMemoryAccessException("Reached end of memory table");
    }
    int maskLength = log2cap / levelCount;
    int maskBits = (base2Exp(maskLength) - 1) << (log2cap - maskLength);
    unsigned int index = (maskBits & address) >> (log2cap - maskLength);
    // Ignore upper bits of address
    address = address & (lowerLevelCapacity - 1);  
    if ((address + size) > lowerLevelCapacity){
        // TODO: ATM, requested memory can be shared just by two indexes, make this better by making it general (while loop))
        if (indexes[index] == NULL){
            indexes[index] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        MemoryChunk* firstChunk = indexes[index]->getMemoryContent(address,lowerLevelCapacity - address);
        if (indexes[index + 1] == NULL){
            indexes[index + 1] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        MemoryChunk* secondChunk = indexes[index + 1]->getMemoryContent(0,address + size - lowerLevelCapacity);
        firstChunk->addChunk(secondChunk);
        // TODO: dismiss second chunk
        delete secondChunk;
        return firstChunk;
    }else{
        if (indexes[index] == NULL){
            indexes[index] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        return indexes[index]->getMemoryContent(address,size);
    }
}

void MiddleMultilevelMemoryTable::setMemoryContent(unsigned int address, MemoryChunk* data){
    if ((address + data->getBytesLength()) > capacity){
        throw new UnalignedMemoryAccessException("Reached end of memory table");
    }
    int maskLength = log2cap / levelCount;
    int maskBits = (base2Exp(maskLength) - 1) << (log2cap - maskLength);
    unsigned int index = (maskBits & address) >> (log2cap - maskLength);
    // Ignore upper bits of address
    address = address & (lowerLevelCapacity - 1);  
    if ((address + data->getBytesLength()) > lowerLevelCapacity){
        // TODO: ATM, memory to write can be shared just by two indexes, make this better by making it general (while loop))
        MemoryChunk* firstChunk = new MemoryChunk(new unsigned char[lowerLevelCapacity - address],lowerLevelCapacity - address);
        MemoryChunk* secondChunk = new MemoryChunk(new unsigned char[address + data->getBytesLength() - lowerLevelCapacity],address + data->getBytesLength() - lowerLevelCapacity);
        firstChunk->copyFrom(data->getBytes());
        secondChunk->copyFrom(&data->getBytes()[lowerLevelCapacity - address]);
        if (indexes[index] == NULL){
            indexes[index] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        indexes[index]->setMemoryContent(address,firstChunk);
        if (indexes[index + 1] == NULL){
            indexes[index + 1] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        indexes[index+1]->setMemoryContent(0,secondChunk);
    }else{
        if (indexes[index] == NULL){
            indexes[index] = MultilevelMemoryTable::createMultilevelMemoryTable(lowerLevelCapacity, levelCount - 1);
        }
        indexes[index]->setMemoryContent(address,data);
    }
}


