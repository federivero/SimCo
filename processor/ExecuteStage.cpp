#include "ExecuteStage.h"
#include "Processor.h"
#include "../architecture/Instruction.h"
#include <string.h>
#include "../interconnect/InterconnectionNetwork.h"
#include "../architecture/ISA.h"

ExecuteStage::ExecuteStage(Processor* processor, int intAluCount, int intAluLatency, 
        int intMultiplierCount, int intMultiplierLatency, int fpAluCount, int fpAluLatency, 
        int fpMultiplierCount, int fpMultiplierLatency, int loadStoreUnitCount, InterconnectionNetwork* dataMemoryInterface){
    this->processor = processor;
    initializeFunctionalUnits(intAluCount, intAluLatency, 
        intMultiplierCount, intMultiplierLatency, fpAluCount, fpAluLatency, 
        fpMultiplierCount, fpMultiplierLatency, loadStoreUnitCount, dataMemoryInterface);
}

ExecuteStage::ExecuteStage(unsigned long id, char* name, Processor* processor,
        int intAluCount, int intAluLatency, int intMultiplierCount, int intMultiplierLatency, 
        int fpAluCount, int fpAluLatency, int fpMultiplierCount, 
        int fpMultiplierLatency, int loadStoreUnitCount, InterconnectionNetwork* dataMemoryInterface):ISimulable(id,name){
    // Create functional units and data structures to manage them
    this->processor = processor;
    initializeFunctionalUnits(intAluCount, intAluLatency, 
        intMultiplierCount, intMultiplierLatency, fpAluCount, fpAluLatency, 
        fpMultiplierCount, fpMultiplierLatency, loadStoreUnitCount, dataMemoryInterface);
}

void ExecuteStage::initializeFunctionalUnits(int intAluCount, int intAluLatency, 
        int intMultiplierCount, int intMultiplierLatency, int fpAluCount, int fpAluLatency, 
        int fpMultiplierCount, int fpMultiplierLatency, int loadStoreUnitCount,
        InterconnectionNetwork* dataMemoryInterface){
    // Integer alus
    this->integerAluCount = intAluCount;
    this->integerAluFUnits = new IntALU*[intAluCount];
    this->availableIntegerAluFUnits = new Queue<IntALU*>(intAluCount);
    for (int i = 0; i < intAluCount; i++){
        this->integerAluFUnits[i] = new IntALU(ISimulable::getNextAvailableId(),
                (char*)"intAlu",
                this,
                intAluLatency);
        this->availableIntegerAluFUnits->queue(this->integerAluFUnits[i]);
    }
    
    // Integer multipliers
    this->integerMultiplierCount = intMultiplierCount;
    this->integerMultiplierFUnits = new FunctionalUnit*[intMultiplierCount];
    this->availableIntegerMultiplierFUnits = new Queue<FunctionalUnit*>(intMultiplierCount);
    for (int i = 0 ; i < intMultiplierCount; i++){
        this->integerMultiplierFUnits[i] = new FunctionalUnit(ISimulable::getNextAvailableId(),
                (char*)"fUnit",
                FUNCTIONAL_UNIT_INT_MULTIPLIER,
                this,
                intMultiplierLatency);
        this->availableIntegerMultiplierFUnits->queue(this->integerMultiplierFUnits[i]);
    }
    
    // Floating point alus
    this->fpAluCount = fpAluCount;
    this->fpAluFUnits = new FunctionalUnit*[fpAluCount];
    this->availableFpAluFUnits = new Queue<FunctionalUnit*>(fpAluCount);
    for (int i = 0; i < fpAluCount; i++){
        this->fpAluFUnits[i] = new FunctionalUnit(ISimulable::getNextAvailableId(),
                (char*)"fpAlu",
                FUNCTIONAL_UNIT_FP_ALU,
                this,
                fpAluLatency);
        this->availableFpAluFUnits->queue(this->fpAluFUnits[i]);
    }
    
    // Floating point multiplier
    this->fpMultiplierCount = fpMultiplierCount;
    this->fpMultiplierFUnits = new FunctionalUnit*[fpMultiplierCount];
    this->availableFpMultiplierFUnits = new Queue<FunctionalUnit*>(fpMultiplierCount);
    for (int i = 0; i < fpMultiplierCount; i++){
        this->fpMultiplierFUnits[i] = new FunctionalUnit(ISimulable::getNextAvailableId(),
                (char*)"fpMultiplier",
                FUNCTIONAL_UNIT_FP_MULTIPLIER,
                this,
                fpMultiplierLatency);
        this->availableFpMultiplierFUnits->queue(this->fpMultiplierFUnits[i]);
    }
    // LoadStore units
    this->loadStoreUnitCount = loadStoreUnitCount;
    this->loadStoreFunctionalUnits = new LoadStoreUnit*[loadStoreUnitCount];
    this->availableLoadStoreUnits = new Queue<LoadStoreUnit*>(loadStoreUnitCount);
    for (int i = 0; i < loadStoreUnitCount ; i++){
        this->loadStoreFunctionalUnits[i] = new LoadStoreUnit(ISimulable::getNextAvailableId(),
                (char*)"loadStoreUni",
                this,
                0);
        loadStoreFunctionalUnits[i]->setDataMemoryInterface(dataMemoryInterface);
        this->availableLoadStoreUnits->queue(this->loadStoreFunctionalUnits[i]);
    }
    // Auxiliary variables
    int totalFunctionalUnits = intAluCount + intMultiplierCount + fpAluCount + fpMultiplierCount;
    releasedFunctionalUnits = new Queue<FunctionalUnit*>(totalFunctionalUnits);
    instructionMapping = new ListMap<FunctionalUnit*,Instruction*>(totalFunctionalUnits);
}

// Pre: There's an available functional unit that can execute the instruction
void ExecuteStage::executeInstruction(Instruction* instruction){
    FunctionalUnit* executingFUnit = NULL;
    ALUInstruction* aluInst;
    JumpInstruction* jumpInstruction;
    IntALU* intAlu;
    LoadStoreUnit* loadStoreUnit;
    LoadStoreInstruction* loadStoreInstruction;
    switch(instruction->getArchetype()->getInstructionType()){
        case INSTRUCTION_TYPE_INT_ALU:
            aluInst = (ALUInstruction*) instruction;
            intAlu = availableIntegerAluFUnits->dequeue();
            intAlu->setALUFunction(aluInst->getALUFunction());
            intAlu->setFirstOperand(aluInst->getSourceOperand(0)->getOperandBinaryValue());
            intAlu->setSecondOperand(aluInst->getSourceOperand(1)->getOperandBinaryValue());
            executingFUnit = intAlu;
            break;
        case INSTRUCTION_TYPE_JUMP:
            jumpInstruction = (JumpInstruction*) instruction;
            intAlu = availableIntegerAluFUnits->dequeue();
            intAlu->setALUFunction(ALU_FUNCTION_MOV);
            intAlu->setFirstOperand(jumpInstruction->getSourceOperand(0)->getOperandBinaryValue());
            executingFUnit = intAlu;
            break;
        case INSTRUCTION_TYPE_LOAD_STORE:
            loadStoreInstruction = (LoadStoreInstruction*) instruction; 
            loadStoreUnit = availableLoadStoreUnits->dequeue();
            int targetAddress = loadStoreInstruction->getAddressOperand()->getOperandBinaryValue();
            MemoryRequest* request = new MemoryRequest(targetAddress,loadStoreInstruction->getLoadStoreSize(),loadStoreInstruction->getLoadStoreType(),processor->getId());
            if (request->getMessageType() == MEMORY_REQUEST_MEMORY_WRITE){
                request->setRawData(
                        MemoryChunk::fromInt(
                                loadStoreInstruction->getReadWriteOperand()->getOperandBinaryValue(),
                                request->getRequestSize(),
                                processor->getISA()->isLittleEndian()));
            }
            loadStoreUnit->setLoadStoreOperation(request);
            executingFUnit = loadStoreUnit;
            break;
    }
    executingFUnit->initExecution();
    instructionMapping->put(executingFUnit,instruction);
}

void ExecuteStage::finishedExecution(FunctionalUnit* funit){
    releasedFunctionalUnits->queue(funit);
    Instruction* executedInstruction = instructionMapping->getData(funit);
    instructionMapping->remove(funit);
    executedInstruction->setInstructionResult(funit->getInstructionResult());
    
    // Get flags value
    // TODO: Should this be here? O_o
    if (funit->isALU()){
        ALU* alu = (ALU*) funit;
        bool nflag = alu->getNFlagValue();
        bool zflag = alu->getZFlagValue();
        bool cflag = alu->getCFlagValue();
        bool vflag = alu->getVFlagValue();
        processor->setNFlagValue(nflag);
        processor->setCFlagValue(cflag);
        processor->setVFlagValue(vflag);
        processor->setZFlagValue(zflag);
        tracer->traceFlagsValue(processor->getId(),zflag,nflag,cflag,vflag);
    }
    processor->instructionExecuted(executedInstruction);
}

void ExecuteStage::initCycle(){
    
}

Processor* ExecuteStage::getProcessor(){
    return processor;
}

LoadStoreUnit** ExecuteStage::getLoadStoreUnits(){
    return loadStoreFunctionalUnits;
}

int ExecuteStage::getLoadStoreUnitCount(){
    return loadStoreUnitCount;
}

void ExecuteStage::setDataMemoryInteface(InterconnectionNetwork* interface){
    for (int i = 0; i < loadStoreUnitCount; i++){
        loadStoreFunctionalUnits[i]->setDataMemoryInterface(interface);
    }
}