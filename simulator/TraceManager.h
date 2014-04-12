/* 
 * File:   TraceManager.h
 * Author: fede
 *
 * Created on 29 de marzo de 2014, 05:36 PM
 */

#ifndef TRACEMANAGER_H
#define	TRACEMANAGER_H

#include "../interconnect/Message.h"

#include <iostream>
#include <fstream>

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
        void traceNewBus(unsigned long deviceId);
        void traceNewRAM(unsigned long deviceId);
        void traceNewCache(unsigned long deviceId);
        void traceNewMemoryRequest(unsigned long messageId, unsigned long address, MessageType type);
        void traceSubmittedMemoryRequest(unsigned long deviceId, unsigned long messageId);
        void traceSubmittedMemoryResponse(unsigned long deviceId, unsigned long messageId);
        
        // Setters
        void setFileName(char* fname);
        void setEnabled(bool ena);

    
};

#endif	/* TRACEMANAGER_H */

