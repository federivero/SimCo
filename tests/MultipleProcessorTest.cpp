/* 
 * File:   newsimpletest.cpp
 * Author: fede
 *
 * Created on 12/04/2014, 11:46:54 AM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% MultipleProcessorTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% TwoCPUOwnCaches (MultipleProcessorTe)" << std::endl;

    std::cout << "%TEST_FINISHED% time=0 TwoCPUOwnCaches (MultipleProcessorTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (MultipleProcessorTest)\n" << std::endl;

    std::cout << "%TEST_FINISHED% time=0 test2 (MultipleProcessorTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

