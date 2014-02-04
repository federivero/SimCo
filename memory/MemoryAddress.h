/* 
 * File:   MemoryAdress.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 05:09 PM
 */

#ifndef MEMORYADDRESS_H
#define	MEMORYADDRESS_H

/* As of 23/01/2014: the memory adress class is the base class for memory
 *  adresses, so far, only 32 bit adresses will be supported */
class MemoryAddress{
private:
public:
    virtual unsigned long toGlobalAddress() = 0;
};

#endif	/* MEMORYADDRESS_H */

