
#include "../simulator/ISimulable.h"
#include "../memory/IMessageDispatcher.h"
#include "../interconnect/InterconnectionNetwork.h"
#include "../architecture/ISA.h"
#include "FetchStage.h"
#include "ExecuteStage.h"
#include "SimpleUnpipedProcessor.h"
#include "RegisterFile.h"

SimpleUnpipedProcessor::SimpleUnpipedProcessor(unsigned long id, char* name, ISA* isa, InterconnectionNetwork* interface)
: Processor(id, name, isa) {
    this->architectedRegisterFile = isa->createArchitectedRegisterFile();
    this->currentStage = SP_STAGE_FETCH;
    this->nextStage = SP_STAGE_FETCH;
    this->fetchStage = new FetchStage(ISimulable::getNextAvailableId(),(char*)"simpleProcessorFetchStage",this,interface,1);
    char* executeStageName = (char*)"simpleProcessorExecuteStage";
    this->executeStage = new ExecuteStage(ISimulable::getNextAvailableId(),executeStageName,this,
            1,1,1,1,1,1,1,1);
    
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
            for (i = 0; i < instructionRegister->getArchetype()->getOperandCount() - 1; i++) {
                switch (instructionRegister->getOperand(i)->getType()) {
                    case OPERAND_TYPE_IMMEDIATE:
                        // Do nothing, operand is already on the instruction
                        break;
                    case OPERAND_TYPE_REGISTER:
                        operand = (RegisterOperand*) instructionRegister->getOperand(i);
                        // Operand has register number, now get the real register and pass it as the operand.
                        // On pipelined processors, care should be taken that the corresponding register is available        
                        switch (operand->getType()) {
                            case REGISTER_TYPE_FP:
                                operand->setRegister(architectedRegisterFile->getFloatingPointRegister(operand->getRegisterNumber()));
                                break;
                            case REGISTER_TYPE_INT:
                                operand->setRegister(architectedRegisterFile->getIntegerRegister(operand->getRegisterNumber()));
                                break;
                        }
                        break;
                        /* TODO!
                    case OPERAND_TYPE_MEMORY:
                        break;
                         * */
                }
            }
            this->nextStage = SP_STAGE_EXECUTE;
            scheduleNextCycleDoAction();
            break;
        case SP_STAGE_EXECUTE:
            if (instructionRegister->getArchetype()->getInstructionType() == INSTRUCTION_TYPE_SYSCALL){
                // Processor ended execution
                nextStage = SP_STAGE_IDLE;
            }else{
                executeStage->executeInstruction(instructionRegister);
            }
            break;
        case SP_STAGE_WRITEBACK:
            // TODO: Think of a generic 'WriteBack' Stage
            // Save result on register or memory
            Operand* destinationOperand = instructionRegister->getDestinationOperand();
            switch(destinationOperand->getType()){
                case OPERAND_TYPE_REGISTER:
                    RegisterOperand* regOperand = (RegisterOperand*) destinationOperand;
                    Register* destinationReg = NULL;
                    switch (operand->getType()) {
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
                    /* TODO!
                case OPERAND_TYPE_MEMORY:
                    break;
                     * */
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
