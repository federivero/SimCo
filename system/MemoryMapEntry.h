/* 
 * File:   MemorySegmentEntry.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 07:10 PM
 */

#ifndef MEMORYSEGMENTENTRY_H
#define	MEMORYSEGMENTENTRY_H

#include "../memory/MemoryDevice.h"

class MemoryDevice;

class MemoryMapEntry{
private:
    /* Global memory map, use binary global adresses */
    unsigned long initialAdress;
    unsigned long endAdress;
    MemoryDevice* device;
public:
    MemoryMapEntry();
    void setInitialAdress(unsigned long adress);
    void setEndAdress(unsigned long adress);
    void setMemoryDevice(MemoryDevice* mDevice);
    unsigned long getInitialAdress();
    unsigned long getEndAdress();
    MemoryDevice* getMemoryDevice();
};

#endif	/* MEMORYSEGMENTENTRY_H */

