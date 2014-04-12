#include <fstream>

#include "StatisticManager.h"
#include "../memory/MemoryDevice.h"
#include "../exceptions/RuntimeException.h"
#include "ExecutionManager.h"
#include "../system/ComputationalSystem.h"
#include "../system/MemorySystem.h"

StatisticManager* StatisticManager::instance = NULL;

StatisticManager::StatisticManager(){
    intStats = new ListMap<string,int>(100);
    realStats = new ListMap<string,double>(100);
}

StatisticManager* StatisticManager::getInstance(){
    if (instance == NULL){
        instance = new StatisticManager();
    }
    return instance;
}

void StatisticManager::setComputationalSystem(ComputationalSystem* system){
    compSystem = system;
}

void StatisticManager::setMemorySystem(MemorySystem* system){
    memSystem = system;
}

void StatisticManager::printStatistics(char* fileName){
    ofstream* file = new ofstream();
    file->open(fileName);
    ExecutionManager* simulator = ExecutionManager::getInstance();
    *file << "SIMULATION STATS" << endl;
    *file << "Total simulated clock cycles " << simulator->getCurrentCycle() << endl << endl;
    
    MemoryDevice** devices = memSystem->getDevices();
    int memDeviceCount = memSystem->getMemoryDeviceCount();
    
    for (int i = 0 ; i < memDeviceCount; i++){
        devices[i]->printStatistics(file);
    }
    file->close();
}

void StatisticManager::addIntStat(string name){
    if (intStats->exists(&name) != -1){
        throw new RuntimeException("Already registered int stat ");
    }
    int* a = new int; *a = 0;
    intStats->put(&name,a);
}

void StatisticManager::addRealStat(string name){
    if (realStats->exists(&name) != -1){
        throw new RuntimeException("Already registered real stat");
    }
    double* d = new double; *d = 0;
    realStats->put(&name,d);
}

void StatisticManager::increaseIntStat(string statName, int ammount){
    int* data = intStats->getData(&statName);
    if (data != NULL){
        *data += ammount;
    }else{
        throw new RuntimeException("Unregistered int stat ");
    }
}

void StatisticManager::setIntStat(string statName, int value){
    int* data = intStats->getData(&statName);
    if (data != NULL){
        *data = value;
    }else{
        throw new RuntimeException("Unregistered int stat");
    }
}

void StatisticManager::setRealStat(string statName, double value){
    double* data = realStats->getData(&statName);
    if (data != NULL){
        *data = value;
    }else{
        throw new RuntimeException("Unregistered real stat");
    }
}
