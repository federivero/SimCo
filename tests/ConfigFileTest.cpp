/* 
 * File:   ConfigFileTest.cpp
 * Author: fede
 *
 * Created on 22/01/2014, 05:15:53 PM
 */

#include <stdlib.h>
#include <iostream>

#include "simulator/ConfigManager.h"
#include <exception>

using namespace std;

/*
 * Simple C++ Test Suite
 */

void test1() {
    try{
        std::cout << "ConfigFileTest test 1" << std::endl;
        ConfigManager::getInstance()->readConfigurationFile();
    }catch(exception e){
        cout << e.what() << endl;
    }
}

void test2() {
    std::cout << "ConfigFileTest test 2" << std::endl;
}

int main2(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% ConfigFileTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (ConfigFileTest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (ConfigFileTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (ConfigFileTest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (ConfigFileTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

