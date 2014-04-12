/* 
 * File:   ComputationalSystem.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:48 AM
 */

#ifndef COMPUTATIONALSYSTEM_H
#define	COMPUTATIONALSYSTEM_H

#include "MemorySystem.h"
#include "../interconnect/InterconnectionNetwork.h"

class InterconnectionNetwork;
class MemorySystem;
class Processor;

class ComputationalSystem{
private:
    InterconnectionNetwork*     network;
    MemorySystem*       memory;
    Processor*  processors;
    int processorCount;
    bool finishedExec;
    
public:
    ComputationalSystem();
    /* Simulates execution of one clock, calculating the state */
    void advanceClock(ComputationalSystem*);
    /* Returns true if execution has finished */
    bool finishedExecution();
};

#endif	/* COMPUTATIONALSYSTEM_H */

