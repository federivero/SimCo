/* 
 * File:   ConfigManager.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:34 AM
 */

#ifndef CONFIGMANAGER_H
#define	CONFIGMANAGER_H

#include <list>
#include <stdlib.h>
#include <map>

enum ParameterName{
    FETCH_WIDTH, INST_FETCH_QUEUE_SIZE, UNRECOGNIZED_PARAM, DIST_MEMORY_DEVICE_COUNT, DISTRIBUTED_MEMORY
};

enum ParameterType{
    INT_P,STRING_P, UNRECOGNIZED_TYPE
};

class ConfigManager{
private:
    static ConfigManager* instance;
    ConfigManager();
    int* intParameters;
    char** stringParameters;
    bool* boolParameters;
public:
    static ConfigManager* getInstance();
    void readConfigurationFile();
    int getIntParameter(ParameterName name);
    char* getStringParameter(ParameterName name);
    bool getBoolParameter(ParameterName name);
};

#endif	/* CONFIGMANAGER_H */

