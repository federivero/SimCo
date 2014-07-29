/* 
 * File:   MemorySegmentEntry.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 07:10 PM
 */

#ifndef MEMORYMAPENTRY_H
#define	MEMORYMAPENTRY_H

class MemoryDevice;

class MemoryMapEntry{
private:
    /* Global memory map, use binary global adresses */
    unsigned long initialAddress;
    unsigned long endAddress;
    MemoryDevice* device;
public:
    MemoryMapEntry();
    void setInitialAddress(unsigned long address);
    void setEndAddress(unsigned long address);
    void setMemoryDevice(MemoryDevice* mDevice);
    unsigned long getInitialAddress();
    unsigned long getEndAddress();
    MemoryDevice* getMemoryDevice();
};

#endif	/* MEMORYMAPENTRY_H */

