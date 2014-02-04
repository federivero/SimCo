
#include "ConfigManager.h"
#include "../common/SimpleFileParser.h"
#include "../exceptions/RuntimeException.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

ConfigManager* ConfigManager::instance = NULL;

ConfigManager::ConfigManager(){
    int arrayLength = 32;
    intParameters = new int[arrayLength];
    stringParameters = new char*[arrayLength];
    boolParameters = new bool[arrayLength];
    for (int i = 0; i < arrayLength; i++){
        stringParameters[i] = new char[256];
        intParameters[i] = 0;
        boolParameters[i] = false;
    }
}

ConfigManager* ConfigManager::getInstance(){
    if (ConfigManager::instance == NULL){
        ConfigManager::instance = new ConfigManager();
    }
    return ConfigManager::instance;
    return NULL;
}

void ConfigManager::readConfigurationFile(){
    SimpleFileParser sfp;
    if (!sfp.open("config.txt")){
        throw new RuntimeException("Unable to open config file");
    }
    sfp.set_single_char_tokens(";=");
    while(sfp.get_next_line()){
        if (sfp.get_num_tokens() > 0){
            string paramName = sfp.get_token(0);
            string paramValue = sfp.get_token(2);
            ParameterName pName = UNRECOGNIZED_PARAM;
            ParameterType pType = UNRECOGNIZED_TYPE;
            if (paramName.compare("fetchWidth") == 0){
                pName = FETCH_WIDTH;
                pType = INT_P;
            }else if (paramName.compare("instFetchQueueSize") == 0){
                pName = INST_FETCH_QUEUE_SIZE;
                pType = INT_P;
            }
            switch(pType){
                case INT_P:
                    this->intParameters[pName] = atoi(paramValue.c_str());
                    break;
                case STRING_P:
                    this->stringParameters[pName] = (char*) paramValue.c_str();
                    break;
                default:
                    break;
            }
        }
    }
}

int ConfigManager::getIntParameter(ParameterName paramName){
    return intParameters[paramName];
}

char* ConfigManager::getStringParameter(ParameterName paramName){
    return stringParameters[paramName];
}

bool ConfigManager::getBoolParameter(ParameterName paramName){
    return boolParameters[paramName];
}





