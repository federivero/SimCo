
#include "FetchStage.h"
#include "../memory/IMessageDispatcher.h"
#include "../architecture/ISA.h"
#include "../architecture/Instruction.h"

FetchStage::FetchStage(Processor* processor, int instructionFetchQueueSize){
    fetchQueue = new Queue<Instruction*>(instructionFetchQueueSize); 
    instructionsQueued = 0;
    this->processor = processor;
    requestedAccesses = new ListMap<InterconnectionNetwork*,bool>(1);
}

FetchStage::FetchStage(unsigned long id, char* name, Processor* processor, InterconnectionNetwork* memoryInterface, int instructionFetchQueueSize)
        :IMessageDispatcher(id,name),instructionMemoryInterface(memoryInterface){
    fetchQueue = new Queue<Instruction*>(instructionFetchQueueSize); 
    instructionsQueued = 0;
    this->processor = processor;
    
    requestedAccesses = new ListMap<InterconnectionNetwork*,bool>(1);
    requestedAccesses->put(memoryInterface,false);
}

void FetchStage::setMemoryInterface(InterconnectionNetwork* memoryInterface){
    this->instructionMemoryInterface = memoryInterface;
    requestedAccesses->put(memoryInterface,false);
}

/* IMessageDispatcher operations */
void FetchStage::accessGranted(InterconnectionNetwork* port){
    if (instructionMemoryInterface == port){
        int instructionSize = processor->getISA()->getInstructionLength();
        currentRequest = new MemoryRequest((int) processor->getPCValue(), instructionSize ,MEMORY_REQUEST_MEMORY_READ,this->id);
        InterconnectionNetworkEvent* memoryRequestEvent = InterconnectionNetworkEvent::createEvent(
                INTERCONNECTION_NETWORK_EVENT_SUBMIT_MESSAGE, 
                instructionMemoryInterface,
                this,
                currentRequest);
        this->simulator->addEvent(memoryRequestEvent,0);
        processor->setPCValue(processor->getPCValue() + instructionSize);
        tracer->traceNewPCValue(processor->getId(),processor->getPCValue());
        // Set variable to notify that the bus was not requested
        requestedAccesses->override(instructionMemoryInterface,false);
    } // TODO: else throw exception ?
    
}

void FetchStage::submitMessage(Message* message, InterconnectionNetwork* port){
    if (port == instructionMemoryInterface){
        MemoryResponse* resp;
        Instruction* instruction;
        switch(message->getMessageType()){
            case MEMORY_RESPONSE:
                resp = (MemoryResponse*) message;
                if (resp->getMemoryRequest() == currentRequest){
                    instruction = processor->getISA()->decodeInstruction(resp->getRawData());
                    cycleFetchedInstrutions++;
                    fetchQueue->queue(instruction);
                    processor->instructionFetched();
                }
                break;
            default:
                // Ignore, broadcast message on shared medium
                break;
        }
    } // TODO: else throw exception for receiving a message from an incorrect interface? 
}

void FetchStage::doFetch(){
    // An instruction needs to be fetched, first request access to network 
    requestAccessToNetwork(instructionMemoryInterface);
}

void FetchStage::initCycle(){
    // Set last cycle fetched instructions as accesible and instructions fetched this cycle to 0
    instructionsQueued += cycleFetchedInstrutions;
    cycleFetchedInstrutions = 0;
}

int FetchStage::getInstructionFetchQueueSize(){
    return instructionsQueued;
}

Instruction* FetchStage::getNextInstructionFetched(){
    instructionsQueued--;
    return fetchQueue->dequeue();
}

/*
void FetchStage::pipeInstruction(Instruction* inst){
    
}
*/

/*
void FetchStage::simulateStage(PipelineStage* retValue){
    for (int i = 0; i < decodeWidth; i++){
        if (!fetchQueue->isEmpty()){
            
        }
        
    }
    
    int instWindowSpace = fetchQueueMaxSize - fetchQueue->getSize();
    int cantInstToQueue = fetchWidth < instWindowSpace? fetchWidth:instWindowSpace; 
    for (int i = 0; i < cantInstToQueue; i++){
        // TODO: pooling?
        MemoryRequest* mreq = new MemoryRequest(instructionPointer,M);
        MemoryResponse* mres = memoryBus->getAdress(mreq);
        Instruction* inst = processor->getISA()->decodeInstruction(mres->getRawData()); 
        FetchStage* fetchStage = (FetchStage*) retValue;
        fetchStage->addIntructionToInstructionWindow(inst);
    }
        
}
*/
/*
void FetchStage::addIntructionToInstructionWindow(Instruction* inst){
    //
    //Queue->addInstruction();
}
*/




