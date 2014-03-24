/* 
 * File:   main.cpp
 * Author: fede
 *
 * Created on 12 de diciembre de 2013, 03:50 PM
 */

#include <cstdlib>

#include "simulator/ConfigManager.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {  
    ConfigManager::getInstance()->readConfigurationFile();
    return 0;
}

