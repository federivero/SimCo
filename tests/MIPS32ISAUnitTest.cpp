/* 
 * File:   MIPS32ISAUnitTest.cpp
 * Author: fede
 *
 * Created on 29/01/2014, 06:47:44 PM
 */

#include <stdlib.h>
#include <iostream>

#include "architecture/MIPS32ISA.h"
#include "architecture/Instruction.h"
#include "memory/MemoryChunk.h"
#include "architecture/MIPS32Loader.h"
#include <exception>

using namespace std;

/*
 * Simple C++ Test Suite
 */

void instructionEncodingTest() {
    std::cout << "MIPS32ISAUnitTest test 1" << std::endl;
    char** params = new char*[3];
    params[0] = (char*) "R4";
    params[1] = (char*) "R1";
    params[2] = (char*) "R1";
    Instruction* inst = MIPS32ISA::getInstance()->buildInstruction((char*)"ADD",params,3);
    std::cout << inst->getSourceRegisterOne() << std::endl;
    std::cout << inst->getSourceRegisterTwo() << std::endl;
    std::cout << inst->getDestinationRegister() << std::endl;
    std::cout << (unsigned int) (inst->getFunction()) << std::endl;
    std::cout << inst->getInstructionOpcode() << std::endl;
    MemoryChunk* rawInst = inst->getRawInstruction();
    std::cout << (unsigned int) (rawInst->getBytes()[0]) << " " << ((unsigned int) (rawInst->getBytes()[1])) 
            << " " << (unsigned int) (rawInst->getBytes()[2]) << " " << (unsigned int) (rawInst->getBytes()[3]) << std::endl;
    if (inst->getSourceRegisterOne() != 1 || 
            inst->getSourceRegisterTwo() != 1 ||
            inst->getDestinationRegister() != 4){
        std::cout << "%TEST_FAILED% time=0 testname=test1 (MIPS32ISAUnitTest) message=Error at encoding instruction" << std::endl;
    }
}

void loaderTest() {
    try{
        std::cout << "MIPS32ISAUnitTest load test" << std::endl;
        MemorySystem* memSystem = new MemorySystem(NULL);
        MIPS32Loader* loader = new MIPS32Loader(memSystem);
        loader->loadProgram((char*)"example1",NULL);
    }catch(exception e){
        cout << e.what() << endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% MIPS32ISAUnitTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (MIPS32ISAUnitTest)" << std::endl;
    instructionEncodingTest();
    std::cout << "%TEST_FINISHED% time=0 test1 (MIPS32ISAUnitTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (MIPS32ISAUnitTest)\n" << std::endl;
    loaderTest();
    std::cout << "%TEST_FINISHED% time=0 test2 (MIPS32ISAUnitTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

