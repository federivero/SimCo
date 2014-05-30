/* 
 * File:   SimpleUnpipedProcessor.h
 * Author: fede
 *
 * Created on 12 de mayo de 2014, 04:48 PM
 */

#ifndef SIMPLEUNPIPEDPROCESSOR_H
#define	SIMPLEUNPIPEDPROCESSOR_H

#include "Processor.h"

class RegisterFile;
class InterconnectionNetwork;

enum SimpleProcessorStage{
    SP_STAGE_FETCH,
    SP_STAGE_DECODE,
    SP_STAGE_EXECUTE,
    SP_STAGE_WRITEBACK,
    SP_STAGE_IDLE // Used to stop de processor
};

/* Class Simple Unpiped Processor simulates a CPU with no pipeline registers. 
   Instructions take 4 cycles at minimum to execute, since fetching takes at
   least a cycle, decoding and operand fetch takes at least another one, 
 * instruction execution and writeback take at least one cycle each*/
class SimpleUnpipedProcessor : public Processor{
    
    private:
        /* Variable to note currently executing stage */
        SimpleProcessorStage currentStage;
        SimpleProcessorStage nextStage;
        
        // Instruction being executed
        Instruction* instructionRegister;
        
    public:
        
        SimpleUnpipedProcessor(unsigned long id, char* name, ISA* isa, InterconnectionNetwork* memoryInterface);
        
        // ISimulable functions 
        void initCycle();
        
        // Main event: check on cycle and do whatever this is supposed to do
        void doCycleAction();
        
        // Processor Functions
        void instructionFetched();
        void instructionExecuted(Instruction* inst);
        bool hasFinishedExecution();
        
        // Internal Operations
        void scheduleNextCycleDoAction();
};

class SimpleUnpipedProcessorEvent : public IEventCallback{
    private:
        SimpleUnpipedProcessor* simulatedProcessor;
    
    public:
        SimpleUnpipedProcessorEvent(EventName eventName, SimpleUnpipedProcessor* simulatedProcessor);
        void simulate();
};
    

#endif	/* SIMPLEUNPIPEDPROCESSOR_H */

