
#include "FetchStage.h"

using namespace std;

FetchStage::FetchStage(InterconnectionNetwork* mbus):memoryBus(mbus){
    ConfigManager* cm = ConfigManager::getInstance();
    fetchWidth = cm->getIntParameter(FETCH_WIDTH);
    fetchQueueMaxSize = cm->getIntParameter(INST_FETCH_QUEUE_SIZE);
}

void FetchStage::pipeInstruction(Instruction* inst){
    /*
    throw new RuntimeException("Should not be invoked -> Fetch Stage gets its "
            "instructions from memory");
     */
}

void FetchStage::simulateStage(PipelineStage* retValue){
    for (int i = 0; i < decodeWidth; i++){
        if (!fetchQueue->isEmpty()){
            
        }
        
    }
    
    int instWindowSpace = fetchQueueMaxSize - fetchQueue->getSize();
    int cantInstToQueue = fetchWidth < instWindowSpace? fetchWidth:instWindowSpace; 
    for (int i = 0; i < cantInstToQueue; i++){
        // TODO: pooling?
        MemoryRequest* mreq = new MemoryRequest(instructionPointer);
        MemoryResponse* mres = memoryBus->getAdress(mreq);
        Instruction* inst = processor->getISA()->decodeInstruction(mres->getRawData()); 
        FetchStage* fetchStage = (FetchStage*) retValue;
        fetchStage->addIntructionToInstructionWindow(inst);
    }
        
}

void FetchStage::addIntructionToInstructionWindow(Instruction* inst){
    //
    //Queue->addInstruction();
}




