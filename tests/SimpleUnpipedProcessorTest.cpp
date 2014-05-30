/* 
 * File:   SimpleUnpipedProcessorTest.cpp
 * Author: fede
 *
 * Created on 17/05/2014, 08:22:29 PM
 */

#include <stdlib.h>
#include <iostream>

#include "simulator/ISimulable.h"
#include "architecture/Instruction.h"
#include "processor/SimpleUnpipedProcessor.h"
#include "simulator/ExecutionManager.h"
#include "architecture/MIPS32ISA.h"
#include "interconnect/Bus.h"
#include "memory/RAM.h"
#include "processor/FetchStage.h"
#include "exceptions/IllegalInstructionSyntaxException.h"

/*
 * Simple C++ Test Suite
 */

void instructionExecutionTest() {
    std::cout << "SimpleUnpipedProcessorTest instructionExecutionTest" << std::endl;
    
    try{
        // Initialize tracer
        TraceManager* tracer = TraceManager::getInstance();
        tracer->setFileName((char*) "SimpleUnpipedProcessorTest.trc");
        tracer->setEnabled(true);
        tracer->startTrace();

        // Initialize simulator
        ExecutionManager* ex = ExecutionManager::getInstance();
        ex->initialize();
        ex->setUnlimitedCycles(false);
        ex->setCycleLimit(100);
        ComputationalSystem* compSys = new ComputationalSystem();
        ex->setComputationalSystem(compSys);
        
        MIPS32ISA* mips32ISA = MIPS32ISA::getInstance();

        Bus* bus = new Bus(ISimulable::getNextAvailableId(),(char*) "CPU_MemoryBus",2,1);
        
        RAM* ram = new RAM(ISimulable::getNextAvailableId(), 2048, 1, 2, bus, (char*) "main memory");

        SimpleUnpipedProcessor* simpleProcessor = new SimpleUnpipedProcessor(ISimulable::getNextAvailableId(),
                (char*) "Simple Processor", mips32ISA, bus);
        
        bus->addDevice(ram,0);
        bus->addDevice(simpleProcessor->getFetchStage(),1);

        
        // Set PC value and first instructions
        simpleProcessor->setPCValue(0);

        char** operands = new char*[3];
        operands[0] = (char*) "R1";
        operands[1] = (char*) "R1";
        operands[2] = (char*) "R1";
        Instruction* xorInst = mips32ISA->buildInstruction((char*)"XOR",operands,3);
        ram->setMemoryContent(xorInst->getRawInstruction(),0);
        
        operands = new char*[3];
        operands[0] = (char*) "R2";
        operands[1] = (char*) "R2";
        operands[2] = (char*) "R2";
        xorInst = mips32ISA->buildInstruction((char*)"XOR",operands,3);
        ram->setMemoryContent(xorInst->getRawInstruction(),4);
        
        Instruction* sysCallInst = mips32ISA->buildInstruction((char*)"SYSCALL",operands,0);
        ram->setMemoryContent(sysCallInst->getRawInstruction(),8);
     
        
        ISimulableEvent* fixedEvent1 = new ISimulableEvent(SIMULABLE_START_CYCLE,simpleProcessor);
        ISimulableEvent* fixedEvent2 = new ISimulableEvent(SIMULABLE_START_CYCLE,bus);
        ISimulableEvent* fixedEvent3 = new ISimulableEvent(SIMULABLE_START_CYCLE,ram);
        ex->addFixedEvent(fixedEvent1);
        ex->addFixedEvent(fixedEvent2);
        ex->addFixedEvent(fixedEvent3);
        
        MemorySystem* memSystem = new MemorySystem(compSys,1,1);
        memSystem->addMemoryDevice(ram,0);
        StatisticManager* stats = StatisticManager::getInstance();
        stats->setMemorySystem(memSystem);
        
        tracer->traceNewBus(bus);
        tracer->traceNewRAM(2);
        tracer->traceNewSimpleUnpipedProcessor(simpleProcessor);
        simpleProcessor->scheduleNextCycleDoAction();
        
        ex->simulate();
    
    }catch(IllegalInstructionSyntaxException e){
        std:cout << e.what() << endl;
    }
    std::cout << "Finished SimpleUnpipedProcessorTest" << endl;
    
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% SimpleUnpipedProcessorTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (SimpleUnpipedProcessorTest)" << std::endl;
    instructionExecutionTest();
    std::cout << "%TEST_FINISHED% time=0 test1 (SimpleUnpipedProcessorTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

