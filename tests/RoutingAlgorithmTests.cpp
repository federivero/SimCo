/* 
 * File:   RoutingAlgorithmTests.cpp
 * Author: fede
 *
 * Created on 19/04/2014, 11:14:50 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void dimensionOrderRoutingTest() {
    std::cout << "DimensionOrderRouting Test" << std::endl;
    
    
}

void test2() {
    std::cout << "RoutingAlgorithmTests test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (RoutingAlgorithmTests) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% RoutingAlgorithmTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% dimensionOrderRoutingTest (RoutingAlgorithmTests)" << std::endl;
    dimensionOrderRoutingTest();
    std::cout << "%TEST_FINISHED% time=0 dimensionOrderRoutingTest (RoutingAlgorithmTests)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (RoutingAlgorithmTests)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (RoutingAlgorithmTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

