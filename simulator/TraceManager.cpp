#include "TraceManager.h"
#include "stdio.h"

using namespace std;

TraceManager* TraceManager::instance = NULL;

TraceManager::TraceManager(){
    file = new ofstream();
    dynamicIdCount = 0;
}

TraceManager* TraceManager::getInstance(){
    if (instance == NULL){
        instance = new TraceManager();
    }
    return instance;
}

void TraceManager::startTrace(){
    if (fileName == NULL){
        //throw new RuntimeException("");
    }
    file->open(fileName);
}

unsigned long TraceManager::getNextDynamicId(){
    dynamicIdCount++;
    return dynamicIdCount;
}

void TraceManager::traceNewCycle(unsigned long cycleNumber){
    if (enabled){
        *file << "Cycle " << cycleNumber << "\n";
    }
}

void TraceManager::traceNewMessage(unsigned long messageId){
    if (enabled){
        *file << "Message-" << messageId << endl;
    }
}

void TraceManager::traceNewRAM(unsigned long deviceId){
    if (enabled){
        *file << "RAM-" << deviceId << endl;
    }
}

void TraceManager::traceNewCache(unsigned long deviceId){
    if (enabled){
        *file << "Cache-" << deviceId << endl;
    }
}

void TraceManager::traceNewBus(unsigned long deciveId){
    if (enabled){
        *file << "Bus-" << deciveId << endl;
    }
}

void TraceManager::traceNewMemoryRequest(unsigned long messageId, unsigned long address, MessageType type){
    if (enabled){
        *file << "MemoryRequest-Id" << messageId << "-Address" << address << "-MessageType" << type <<endl; 
    }
}

void TraceManager::traceSubmittedMemoryRequest(unsigned long deviceId,unsigned long messageId){
    if (enabled){
        *file << "MemoryRequest-" << deviceId << "-" << messageId << endl;
    }
}

void TraceManager::traceSubmittedMemoryResponse(unsigned long deviceId, unsigned long messageId){
    if (enabled){
        *file << "MemoryResponse-" << deviceId << "-" << messageId << endl;
    }
}
        
void TraceManager::finishTracing(){
    file->close();
}

/* Setters */
void TraceManager::setFileName(char* fname){
    fileName = fname;
}

void TraceManager::setEnabled(bool ena){
    enabled = ena;
}






