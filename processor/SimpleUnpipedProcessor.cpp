
#include "../simulator/ISimulable.h"
#include "../memory/IMessageDispatcher.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "../architecture/ISA.h"
#include "FetchStage.h"
#include "ExecuteStage.h"
#include "SimpleUnpipedProcessor.h"
#include "RegisterFile.h"

SimpleUnpipedProcessor::SimpleUnpipedProcessor(){
    this->currentStage = SP_STAGE_FETCH;
    this->nextStage = SP_STAGE_FETCH;
    this->fetchStage = new FetchStage(this,1);
    this->executeStage = new ExecuteStage(this,1,1,1,1,1,1,1,1,1, NULL);
}

SimpleUnpipedProcessor::SimpleUnpipedProcessor(unsigned long id, char* name, ISA* isa, 
                InterconnectionNetwork* instructionMemoryInterface, InterconnectionNetwork* dataMemoryInterface)
: Processor(id, name, isa) {
    this->architectedRegisterFile = isa->createArchitectedRegisterFile();
    this->currentStage = SP_STAGE_FETCH;
    this->nextStage = SP_STAGE_FETCH;
    this->fetchStage = new FetchStage(ISimulable::getNextAvailableId(),(char*)"simpleProcessorFetchStage",this,instructionMemoryInterface,1);
    char* executeStageName = (char*)"simpleProcessorExecuteStage";
    this->executeStage = new ExecuteStage(ISimulable::getNextAvailableId(),executeStageName,this,
            1,1,1,1,1,1,1,1,1,dataMemoryInterface);   
}

IMessageDispatcher* SimpleUnpipedProcessor::setInstructionMemoryInterface(InterconnectionNetwork* memoryInterface){
    this->fetchStage->setMemoryInterface(memoryInterface);
    return this->fetchStage;
}

void SimpleUnpipedProcessor::setDataMemoryInterface(InterconnectionNetwork* memoryInterface, List<IMessageDispatcher*> *list){
    this->executeStage->setDataMemoryInteface(memoryInterface);
    LoadStoreUnit** loadStoreUnits =  this->executeStage->getLoadStoreUnits();
    for (int i = 0; i < this->executeStage->getLoadStoreUnitCount(); i++){
        list->add(loadStoreUnits[i]->getMemoryAdapter());
    }
}

void SimpleUnpipedProcessor::setName(char* name){
    this->name = name;
    fetchStage->setName((char*)((string) name + (string) " - FetchStage").c_str());
    executeStage->setName((char*)((string) name + (string) " - ExecuteStage").c_str());
}

void SimpleUnpipedProcessor::instructionFetched() {
    this->nextStage = SP_STAGE_DECODE;
    // Cycle event for next cycle to process decode stage
    scheduleNextCycleDoAction();
}

void SimpleUnpipedProcessor::instructionExecuted(Instruction* inst) {
    // Since this processor has only one instruction on float at any given time. 
    // inst should be equal to instructionRegister

    this->nextStage = SP_STAGE_WRITEBACK;
    // Cycle event for next cycle to process decode stage
    scheduleNextCycleDoAction();
}

bool SimpleUnpipedProcessor::hasFinishedExecution(){
    return (currentStage == SP_STAGE_IDLE);
}

void SimpleUnpipedProcessor::scheduleNextCycleDoAction() {
    SimpleUnpipedProcessorEvent* event = new SimpleUnpipedProcessorEvent(SIMPLE_UNPIPED_PROCESSOR_DO_CYCLE_ACTION, this);
    simulator->addEvent(event, 1);
}

void SimpleUnpipedProcessor::doCycleAction() {
    RegisterOperand* operand;
    int i;
    switch (currentStage) {
        case SP_STAGE_FETCH:
            fetchStage->doFetch();
            break;
        case SP_STAGE_DECODE:
            // Get first decoded instruciton from fetchStage
            instructionRegister = fetchStage->getNextInstructionFetched();
            tracer->traceInstructionRegisterValue(id,instructionRegister);
            // TODO: Check for unfetched memory operands
            for (i = 0; i < instructionRegister->getArchetype()->getSourceOperandCount(); i++) {
                switch (instructionRegister->getSourceOperand(i)->getType()) {
                    case OPERAND_TYPE_IMMEDIATE:
                        // Do nothing, operand is already on the instruction
                        break;
                    case OPERAND_TYPE_REGISTER:
                        operand = (RegisterOperand*) instructionRegister->getSourceOperand(i);
                        // Operand has register number, now get the real register and pass it as the operand.
                        // On pipelined processors, care should be taken that the corresponding register is available        
                        switch (operand->getRegisterType()) {
                            case REGISTER_TYPE_FP:
                                operand->setOperandBinaryValue(architectedRegisterFile->getFloatingPointRegister(operand->getRegisterNumber())->getRegisterValue());
                                break;
                            case REGISTER_TYPE_INT:
                                operand->setOperandBinaryValue(architectedRegisterFile->getIntegerRegister
                                        (operand->getRegisterNumber())->getRegisterValue());
                                break;
                        }
                        break;
                    case OPERAND_TYPE_INDEXED:
                        IndexedOperand* indexedOperand = (IndexedOperand*) instructionRegister->getSourceOperand(i);
                        // Operand has register number, now get the real register and pass it as the operand.
                        // On pipelined processors, care should be taken that the corresponding register is available        
                        indexedOperand->setOperandBinaryValue(architectedRegisterFile->getIntegerRegister
                                (indexedOperand->getRegisterNumber())->getRegisterValue() + indexedOperand->getImmediateValue());
                        break;
                    //case OPERAND_TYPE_MEMORY:
                        // Not possible on MIPS32
                    //    break;
                }
            }
            this->nextStage = SP_STAGE_EXECUTE;
            scheduleNextCycleDoAction();
            break;
        case SP_STAGE_EXECUTE:
            if (instructionRegister->getArchetype()->getInstructionType() == INSTRUCTION_TYPE_SYSCALL){
                // Processor ended execution
                nextStage = SP_STAGE_IDLE;
                // Do generic processor finished execution work
                finishedExecution();
            }else{
                executeStage->executeInstruction(instructionRegister);
            }
            break;
        case SP_STAGE_WRITEBACK:
            // TODO: Think of a generic 'WriteBack' Stage
            // Save result on register or memory
            if  (instructionRegister->getArchetype()->getDestinationOperandCounts() > 0){
                Operand* destinationOperand = instructionRegister->getDestinationOperand(0);
                SpecialRegisterOperand* specialRegisterOperand;
                RegisterOperand* regOperand;
                Register* destinationReg;
                switch(destinationOperand->getType()){
                    case OPERAND_TYPE_REGISTER:
                        regOperand = (RegisterOperand*) destinationOperand;
                        destinationReg = NULL;
                        switch (regOperand->getRegisterType()) {
                            case REGISTER_TYPE_FP:
                                destinationReg = architectedRegisterFile->getFloatingPointRegister(regOperand->getRegisterNumber());
                                break;
                            case REGISTER_TYPE_INT:
                                destinationReg = architectedRegisterFile->getIntegerRegister(regOperand->getRegisterNumber());
                                break;
                        }
                        destinationReg->setRegisterValue(instructionRegister->getInstructionResult());
                        tracer->traceRegisterValue(id,destinationReg);
                        break;
                    case OPERAND_TYPE_SPECIAL_REGISTER:
                        specialRegisterOperand = (SpecialRegisterOperand*) destinationOperand;
                        switch(specialRegisterOperand->getSpecialRegisterType()){
                            case SPECIAL_REGISTER_PC:
                                this->PC = ((InstructionResultInt*)instructionRegister->getInstructionResult())->getResult();
                                tracer->traceNewPCValue(id,PC);
                                break;
                        }
                        break;
                        /* TODO!
                    case OPERAND_TYPE_MEMORY:
                        break;
                         * */
                }
            }
            // Count executed instructions
            executedInstructions++;
            switch(instructionRegister->getArchetype()->getInstructionType()){
                case INSTRUCTION_TYPE_LOAD_STORE:
                    memoryInstructions++;
                    break;
                case INSTRUCTION_TYPE_FP_ALU:
                case INSTRUCTION_TYPE_INT_ALU:
                    aluInstructions++;
                    break;
                case INSTRUCTION_TYPE_JUMP:
                case INSTRUCTION_TYPE_BRANCH:
                    jumpInstructions++;
                    break;
            }
            nextStage = SP_STAGE_FETCH;
            scheduleNextCycleDoAction();
            break;
    }
}

void SimpleUnpipedProcessor::initCycle() {
    currentStage = nextStage;
}

/* Simulator events */
SimpleUnpipedProcessorEvent::SimpleUnpipedProcessorEvent(EventName eventName, SimpleUnpipedProcessor* simulatedProcessor)
: IEventCallback(eventName) {
    this->simulatedProcessor = simulatedProcessor;
}

void SimpleUnpipedProcessorEvent::simulate() {
    switch (eventName) {
        case SIMPLE_UNPIPED_PROCESSOR_DO_CYCLE_ACTION:
            simulatedProcessor->doCycleAction();
            break;
        default:
            break;
    }
}

void SimpleUnpipedProcessor::scheduleInitExecutionEvent(){
    scheduleNextCycleDoAction();
}

/* Statistics function */
void SimpleUnpipedProcessor::printStatistics(ofstream* file){
    *file << "Simple Unpiped Processor " << endl;
    Processor::printStatistics(file);
    // TODO: print fetch stage andd execute stage statistics
    
    *file << endl;
}

void SimpleUnpipedProcessor::traceSimulable(){
    tracer->traceNewSimpleUnpipedProcessor(this);
    this->architectedRegisterFile->traceRegisterFile(this->id, tracer);
}
