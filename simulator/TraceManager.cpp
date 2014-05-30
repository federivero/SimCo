#include "TraceManager.h"
#include "stdio.h"
#include "../simulator/ISimulable.h"
#include "../memory/Cache.h"
#include "../interconnect/Bus.h"
#include "../memory/MemoryRequest.h"
#include "../memory/MemoryResponse.h"
#include "../interconnect/Message.h"
#include "../processor/Register.h"
#include "../architecture/Instruction.h"
#include "../processor/SimpleUnpipedProcessor.h"

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

void TraceManager::traceNewCache(Cache* cache){
    if (enabled){
        *file << "Cache-id:" << cache->getId() 
                << "-name:" << cache->getName() 
                << "-setCount:" << cache->getSetCount() 
                << "-lineSize:" << cache->getLineSize()
                << "-associativity:" << cache->getAssociativity()
                << endl;
    }
}

void TraceManager::traceCacheLineChange(unsigned long cacheId, unsigned int lineNumber, CacheLineEntry* cacheLine){
    if (enabled){
        *file << "CacheLine-cacheId:" << cacheId
                << "-lineNumber:" << lineNumber
                << "-tag:" << cacheLine->getTag()
                << "-state:" << cacheLine->getState()
                << "-data:";
        for (int j = 0; j < cacheLine->getLineSize() ; j++)
            *file << cacheLine->getLineData()[j];
        *file << endl;
    }
}

void TraceManager::traceNewBus(Bus* bus){
    if (enabled){
        *file << "Bus-id:" << bus->getId() 
                << "-name:" << bus->getName()
                << "-width:" << bus->getBusWidth()
                << endl;
    }
}

void TraceManager::traceSubmittedMessageToBus(Bus* bus, Message* message){
    if (enabled){
        *file << "BusMessage-busId:" << bus->getId() 
                << "-messageId:" << message->getMessageId()
                << "-messageType:" << message->getMessageType();
        MemoryRequest* req;
        MemoryResponse* resp;
        switch(message->getMessageType()){
            case MEMORY_REQUEST_MEMORY_WRITE:
                req = (MemoryRequest*) message;
                *file << "-address:" << req->getMemoryAdress()
                        << "-data:";
                traceMemoryChunk(req->getRawData());
                *file << endl;
                break;
            case MEMORY_REQUEST_MEMORY_READ:
            case CACHE_COHERENCE_INVALIDATE:
                req = (MemoryRequest*) message;
                *file << "-address:" << req->getMemoryAdress()
                << endl;
                break;
            case MEMORY_RESPONSE:
                resp = (MemoryResponse*) message;
                if (resp->getRawData()!=NULL){
                    // Null body responses come from acks to memory writes
                    *file << "-data:";
                    traceMemoryChunk(resp->getRawData());
                }
                *file << endl;
                break;
            default:
                break;
        }
    }
}

/* Internal operation for tracing MemoryChunks to traceFile*/
void TraceManager::traceMemoryChunk(MemoryChunk* chunk){
    unsigned char* data = chunk->getBytes();
    for (int j = 0; j < chunk->getBytesLength() ; j++)
        *file << data[j];
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

// Processor tracing operations 
void TraceManager::traceNewSimpleUnpipedProcessor(SimpleUnpipedProcessor* simpleProcessor){
    if (enabled){
        *file << "Processor-type:SimpleUnpipedProcessor-id:" 
                << simpleProcessor->getId() 
                << "-name:" << simpleProcessor->getName() << endl;
    }
}

void TraceManager::traceNewPCValue(unsigned long processorId, unsigned long pcValue){
    if (enabled){
        *file << "PCValue-processorId:" << processorId 
                << "-pcValue:" << pcValue << endl;
    }
}

void TraceManager::traceInstructionRegisterValue(unsigned long processorId, Instruction* registerValue){
    if (enabled){
        *file << "InstructionRegisterValue-processorId:" << processorId
                << "-irValue:";
        traceMemoryChunk(registerValue->getRawInstruction());
        *file << endl;
    }
}

void TraceManager::traceRegisterValue(unsigned long processorId, Register* reg){
    if (enabled){
        *file << "RegisterValue-processorId:" << processorId
                << "-registerNumber:" << reg->getRegisterNumber() 
                << "-value:";
        reg->printRegisterValue(file);
        *file << endl;
    }
}

void TraceManager::traceFlagsValue(unsigned long processorId, bool zflag, bool nflag, bool cflag, bool vflag){
    if (enabled){
        *file << "FlagsValue-processorId:" << processorId
                << "-zFlag:" << zflag
                << "-nFlag:" << nflag
                << "-cFlag:" << cflag
                << "-vFlag:" << vflag << endl;
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






