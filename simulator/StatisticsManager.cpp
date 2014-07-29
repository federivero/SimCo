#include <fstream>

#include "StatisticManager.h"
#include "../memory/MemoryDevice.h"
#include "../exceptions/RuntimeException.h"
#include "ExecutionManager.h"
#include "../system/ComputationalSystem.h"
#include "../system/MemorySystem.h"
#include "../exceptions/RuntimeException.h"
#include "../processor/Processor.h"

StatisticManager* StatisticManager::instance = NULL;

StatisticManager::StatisticManager(){
    intStats = new ListMap<string*,int>(100);
    realStats = new ListMap<string*,double>(100);
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
    if (!file->is_open()){
        throw new RuntimeException("Problem opening statistics file");
    }
    
    ExecutionManager* simulator = ExecutionManager::getInstance();
    *file << "SIMULATION STATS" << endl;
    *file << "Total simulated clock cycles " << simulator->getCurrentCycle() << endl << endl;
    
    Processor** processors = compSystem->getProcessors();
    int processorCount = compSystem->getProcessorCount();
    for (int i = 0; i < processorCount; i++){
        processors[i]->printStatistics(file);
    }
    
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
    intStats->put(&name,0);
}

void StatisticManager::addRealStat(string name){
    if (realStats->exists(&name) != -1){
        throw new RuntimeException("Already registered real stat");
    }
    realStats->put(&name,0);
}

void StatisticManager::increaseIntStat(string statName, int ammount){
    if (intStats->exists(&statName) == -1){
        throw new RuntimeException("Unregistered int stat ");
    }
    int data = intStats->getData(&statName);
    intStats->override(&statName,ammount + data);
}

void StatisticManager::setIntStat(string statName, int value){
    if (intStats->exists(&statName) == -1){
        throw new RuntimeException("Unregistered int stat ");
    }
    intStats->override(&statName,value);
}

void StatisticManager::setRealStat(string statName, double value){
    if (realStats->exists(&statName) == -1){
        throw new RuntimeException("Unregistered int stat ");
    }
    realStats->override(&statName,value);
}
