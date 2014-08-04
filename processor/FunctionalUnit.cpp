#include "FunctionalUnit.h"
#include "ExecuteStage.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "Processor.h"
#include "../architecture/ISA.h"

// ISimulable operations
void FunctionalUnit::initCycle(){
}

FunctionalUnit::FunctionalUnit(unsigned long id, char* name, FunctionalUnitType funcType, ExecuteStage* execStage, int latency)
        :ISimulable(id,name),type(funcType){
    this->latency = latency;
    this->executionStage = execStage;
}

FunctionalUnitType FunctionalUnit::getType(){
    return type;
}

InstructionResult* FunctionalUnit::getInstructionResult(){
    // TODO: This function has to be pure virtual when all implementations of FunctionalUnit are implemented
    return NULL;
}

bool FunctionalUnit::isALU(){
    // Overriden on ALU class to correct this
    return false;
}

// LoadStore Unit operations 
LoadStoreUnit::LoadStoreUnit(unsigned long id, char* name, ExecuteStage* execStage, int latency)
        :FunctionalUnit(id,name,FUNCTIONAL_UNIT_LOADSTOREUNIT,execStage,latency)
{
    
}

void LoadStoreUnit::setMemoryResponse(MemoryResponse* memoryResponse){
    this->memoryResponse = memoryResponse;
}
        
void LoadStoreUnit::setDataMemoryInterface(InterconnectionNetwork* dataMemoryInterface){
    dataMemoryAdapter = new LoadStoreUnitMemoryAdapter(this, dataMemoryInterface);
}

void LoadStoreUnit::setLoadStoreOperation(MemoryRequest* request){
    this->targetRequest = request;
}

void LoadStoreUnit::initExecution(){
    dataMemoryAdapter->sendMessageThroughInterface(targetRequest);
}

void LoadStoreUnit::endExecution(){
    // Execution ended, tell execcution stage to get results
    if (targetRequest->getMessageType() == MEMORY_REQUEST_MEMORY_READ){
        int result = memoryResponse->getRawData()->asInt(executionStage->getProcessor()->getISA()->isLittleEndian());
        this->instructionResult = new InstructionResultInt(result);
    }
    executionStage->finishedExecution(this);
}

InstructionResult* LoadStoreUnit::getInstructionResult(){
    return instructionResult;
}

LoadStoreUnitMemoryAdapter* LoadStoreUnit::getMemoryAdapter(){
    return dataMemoryAdapter;
}

// LoadStoreUnitMemoryAdapter
LoadStoreUnitMemoryAdapter::LoadStoreUnitMemoryAdapter(LoadStoreUnit* loadStoreUnit, InterconnectionNetwork* port){
    this->loadStoreUnit = loadStoreUnit;
    this->memoryInterface = port;
}

void LoadStoreUnitMemoryAdapter::submitMessage(Message* message, InterconnectionNetwork* port){
    if (message->getMessageType() == MEMORY_RESPONSE){
        MemoryResponse* memoryResponse = (MemoryResponse*) message;
        if (memoryResponse->getMemoryRequest() == this->message){
            // Got response from message, time to end execution
            loadStoreUnit->setMemoryResponse(memoryResponse);
            loadStoreUnit->endExecution();
        }
    }
}

void LoadStoreUnitMemoryAdapter::accessGranted(InterconnectionNetwork* port){
    // TODO: check if port != mmemoryInteface?
    memoryInterface->submitMessage(message,this);
}

void LoadStoreUnitMemoryAdapter::sendMessageThroughInterface(Message* message){
    this->message = message;
    memoryInterface->requestAccess(this);
}

/* ALU Operations*/
ALU::ALU(unsigned long id, char* name, FunctionalUnitType type, ExecuteStage* execStage, int latency)
        :FunctionalUnit(id,name,type,execStage,latency){
    
}

bool ALU::getZFlagValue(){
    return zFlag;
}

bool ALU::getNFlagValue(){
    return nFlag;
}

bool ALU::getCFlagValue(){
    return cFlag;
}

bool ALU::getVFlagValue(){
    return vFlag;
}
    
bool ALU::isALU(){
    return true;
}

/* IntALU Operations */

IntALU::IntALU(unsigned long id, char* name, ExecuteStage* execStage, int latency)
    :ALU(id,name,FUNCTIONAL_UNIT_INT_ALU,execStage,latency){
    
}

void IntALU::setALUFunction(ALUFunction function){
    this->function = function;
}

void IntALU::setFirstOperand(long operand){
    this->firstOperand = operand;
}

void IntALU::setSecondOperand(long operand){
    this->secondOperand = operand;
}

void IntALU::setThirdOperand(long thirdOperand){
    this->thirdOperand = thirdOperand;
}

InstructionResult* IntALU::getInstructionResult(){
    return instructionResult;
}

void IntALU::initExecution(){
    // Calculate instruction result and schedule event to simulate instruction latency
    int result;
    
    switch(this->function){
        case ALU_FUNCTION_AND:
            result = firstOperand & secondOperand;
            break;
        case ALU_FUNCTION_INT_ADD:
            result = firstOperand + secondOperand;
            if (result < (firstOperand + secondOperand)){
                cFlag = 1;
            }
            break;
        case ALU_FUNCTION_INT_ADD_UNSIGNED:
            result = ((unsigned int) firstOperand) + (unsigned int) secondOperand;
            if (result < (((unsigned int) firstOperand) + (unsigned int) secondOperand)){
                cFlag = 1;
            }
            break;
        case ALU_FUNCTION_INT_SUB:
            result = firstOperand - secondOperand;
            break;
        case ALU_FUNCTION_MOV:
            result = firstOperand;
            break;
        case ALU_FUNCTION_OR:
            result = firstOperand | secondOperand;
            break;
        case ALU_FUNCTION_XOR:
            result = firstOperand ^ secondOperand;
            break;
        case ALU_FUNCTION_SHIFT_RIGHT_LOGICAL:
            result = firstOperand >> secondOperand;
            break;
        case ALU_FUNCTION_SHIFT_LEFT:
            result = firstOperand << secondOperand;
            if (result < (firstOperand << secondOperand)){
                cFlag = 1;
                vFlag = 1;
            }
            break;
        case ALU_FUNCTION_SHIFT_RIGHT_ARITHMETIC:
            result = firstOperand >> secondOperand;
            if (firstOperand < 0){
                // if negative, add ones at the beggining
                int oneCount = secondOperand;
                if (oneCount > 32){
                    oneCount = 32;
                }
                int realBits = 32 - oneCount;
                if (realBits < 0){
                    realBits = 0;
                }
                int oneMask = ((1 << oneCount) - 1) << (realBits);
                result = result | oneMask;
            }
            break;
        case ALU_FUNCTION_MOV_LOWER_16_BITS:
            result = (firstOperand & 0xFFFF0000) | secondOperand;
            break;
        case ALU_FUNCTION_MOV_UPPER_16_BITS:
            result = (firstOperand & 0x0000FFFF) | (secondOperand << 16);
            break;
        case ALU_FUNCTION_CONDITIONAL_MOV_EQUALS:
            if (firstOperand == secondOperand){
                result = 1;
            }else{
                result = 0;
            }
            break;
        case ALU_FUNCTION_CONDITIONAL_MOV_NOT_EQUALS:
            if (firstOperand != secondOperand){
                result = 1;
            }else{
                result = 0;
            }
            break;
        case ALU_FUNCTION_CONDITIONAL_MOV_GREATER:
            // two's complement comparison
            if (firstOperand > secondOperand){
                result = 1;
            }else{
                result = 0;
            }
            break;
        case ALU_FUNCTION_CONDITIONAL_MOV_LESS_OR_EQUAL:
            // two's complement comparison
            if (firstOperand <= secondOperand){
                result = 1;
            }else{
                result = 0;
            }
            break;
        default:
            // TODO: Throw exception
            break;
    }
    if (result < 0){
        nFlag = 1;
    }else{
        nFlag = 0;
    }
    if (result == 0){
        zFlag = 1;
    }else{
        zFlag = 0;
    }
    
    // TODO: Object Pooling?
    // TODO: Think of an extended class hierarchy to support 32 and 64 bit architectures
    instructionResult = new InstructionResultInt(result);
    
    FunctionalUnitEvent* event = new FunctionalUnitEvent(FUNCTIONAL_UNIT_EXECUTION_END,this);
    this->simulator->addEvent(event,latency-1);
}

void IntALU::endExecution(){
    executionStage->finishedExecution(this);
}

/* FunctionalUnitEvent Operations */
FunctionalUnitEvent::FunctionalUnitEvent(EventName name, FunctionalUnit* funit):IEventCallback(name){
    this->functionalUnit = funit;
}

void FunctionalUnitEvent::simulate(){
    switch(eventName){
        case FUNCTIONAL_UNIT_EXECUTION_INIT:
            functionalUnit->initExecution();
            break;
        case FUNCTIONAL_UNIT_EXECUTION_END:
            functionalUnit->endExecution();
            break;
    }
}