/* 
 * File:   MemoryChip.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 07:10 PM
 */

#ifndef MEMORYDEVICE_H
#define	MEMORYDEVICE_H

#include "MemoryChunk.h"
#include "MemoryAddress.h"
#include "../system/InterconnectionNetwork.h"

/* Base class for all memory devices */
class MemoryDevice{
private:
        
public:
    virtual void setMemoryContent(MemoryChunk* data, MemoryAddress* address) = 0;
    virtual MemoryChunk* getMemoryContent(MemoryAddress* address, InterconnectionNetwork port) = 0;
};

#endif	/* MEMORYCHIP_H */

