/* 
 * File:   SimpleUnpipedProcessor.h
 * Author: fede
 *
 * Created on 12 de mayo de 2014, 04:48 PM
 */

#ifndef SIMPLEUNPIPEDPROCESSOR_H
#define	SIMPLEUNPIPEDPROCESSOR_H

#include "Processor.h"
#include "SimpleProcessorStage.h"

class RegisterFile;
class InterconnectionNetwork;


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
        // Constructors
        SimpleUnpipedProcessor();
        SimpleUnpipedProcessor(unsigned long id, char* name, ISA* isa, InterconnectionNetwork* instructionMemoryInterface, InterconnectionNetwork* dataMemoryInterface);
        
        // Setters
        void setName(char* name);
        // Memory interface setters. Returns a reference to the object using it
        IMessageDispatcher* setInstructionMemoryInterface(InterconnectionNetwork* memoryInterface);
        void setDataMemoryInterface(InterconnectionNetwork* memoryInterface, List<IMessageDispatcher*> *list);
        // ISimulable functions 
        void initCycle();
        
        // Main event: check on cycle and do whatever this is supposed to do
        void doCycleAction();
        
        // Processor Functions
        void instructionFetched();
        void instructionExecuted(Instruction* inst);
        bool hasFinishedExecution();
        
        // Statistic function
        void printStatistics(ofstream* file);
        void traceSimulable();
        
        // Internal Operations
        void scheduleNextCycleDoAction();
        void scheduleInitExecutionEvent();
};

class SimpleUnpipedProcessorEvent : public IEventCallback{
    private:
        SimpleUnpipedProcessor* simulatedProcessor;
    
    public:
        SimpleUnpipedProcessorEvent(EventName eventName, SimpleUnpipedProcessor* simulatedProcessor);
        void simulate();
};
    

#endif	/* SIMPLEUNPIPEDPROCESSOR_H */

