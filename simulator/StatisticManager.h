/* 
 * File:   StatisticsManager.h
 * Author: fede
 *
 * Created on 6 de abril de 2014, 11:32 PM
 */

#ifndef STATISTICMANAGER_H
#define	STATISTICMANAGER_H

#include "../common/Map.h"
#include <string>

using namespace std;
class MemorySystem;
class ComputationalSystem;

class StatisticManager{
    private:
        /* Structure to hold the statistics */
        GenMap<string*,int> * intStats;
        GenMap<string*,double> * realStats;
        
        MemorySystem* memSystem;
        ComputationalSystem* compSystem;
        
        static StatisticManager* instance;
        StatisticManager();
    public:
        static StatisticManager* getInstance();
        
        void printStatistics(char* fileName);
        
        // Setters
        void setMemorySystem(MemorySystem* system);
        void setComputationalSystem(ComputationalSystem* system);
        
        // Not used for the moment
        void addIntStat(string name);
        void addRealStat(string name);
        
        void increaseIntStat(string statName, int ammount);
        void setIntStat(string statName, int ammount);
        void setRealStat(string statName, double ammount);
};

#endif	/* STATISTICMANAGER_H */

