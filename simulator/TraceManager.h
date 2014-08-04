/* 
 * File:   TraceManager.h
 * Author: fede
 *
 * Created on 29 de marzo de 2014, 05:36 PM
 */

#ifndef TRACEMANAGER_H
#define	TRACEMANAGER_H

#include "../interconnect/Message.h"        
#include "../processor/SimpleProcessorStage.h"

#include <iostream>
#include <fstream>

class Cache;
class CacheLineEntry;
class Bus;
class MemoryChunk;
class Register;
class Instruction;
class RAM;
class SimpleUnpipedProcessor;

using namespace std;

/* The TraceManager class is responsible for storing the information the 
 * simulator calculates. Being an interface, leaves the room open for diferent
 * implementations. 
 */
class TraceManager{
    
    private:
        // funcional simulators do not have to leave an execution trace 
        bool enabled;
        // Information about the file storing the trace
        char* fileName;
        ofstream* file;
        
        static TraceManager* instance;
        TraceManager();
        
        // Dynamic ID
        unsigned long dynamicIdCount;
    public:
        static TraceManager* getInstance();
            // Function called for initialization
        void startTrace();
        void finishTracing();    
        
        // DynamicIdFunction
        unsigned long getNextDynamicId();
        
        void traceNewCycle(unsigned long cycleNumber);
        void traceNewMessage(unsigned long messageId);
        void traceNewBus(Bus* bus);
        void traceNewRAM(RAM* ram);
        void traceNewCache(Cache* cache);
        void traceNewMemoryRequest(unsigned long messageId, unsigned long address, MessageType type);
        void traceSubmittedMemoryRequest(unsigned long deviceId, unsigned long messageId);
        void traceSubmittedMemoryResponse(unsigned long deviceId, unsigned long messageId);
        
        // Processor Trace operations
        void traceNewSimpleUnpipedProcessor(SimpleUnpipedProcessor* simpleProcessor);
        void traceNewRegister(unsigned long processorId, Register* reg);
        void traceNewPCValue(unsigned long processorId, unsigned long pcValue);
        void traceRegisterValue(unsigned long processorId, Register* reg);
        void traceFlagsValue(unsigned long processorId, bool zflag, bool nflag, bool cflag, bool vflag);
        void traceInstructionRegisterValue(unsigned long processorId, Instruction* registerValue);
        void traceSimpleUnpipedProcessorStage(unsigned long processorId, SimpleProcessorStage stage);
        
        void traceSubmittedMessageToBus(Bus* bus, Message* message);
        void traceCacheLineChange(unsigned long id, unsigned int cacheLineNumber, CacheLineEntry* cacheLine);
        
        /* Internal Operations */
        void traceMemoryChunk(MemoryChunk* chunk);
        void traceByteArrayAsHex(unsigned char* data, int length);
        
        // Setters
        void setFileName(char* fname);
        void setEnabled(bool ena);

    
};

#endif	/* TRACEMANAGER_H */

