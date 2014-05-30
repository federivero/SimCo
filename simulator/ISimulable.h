/* 
 * File:   ISimulable.h
 * Author: fede
 *
 * Created on 23 de marzo de 2014, 10:18 PM
 */

#ifndef ISIMULABLE_H
#define	ISIMULABLE_H

#include "IEventCallback.h"
#include "StatisticManager.h"
#include "ExecutionManager.h"
#include "TraceManager.h"

class ISimulable{
    private:
        static unsigned long lastAvailableId;
    protected:
        unsigned long id;
        char* name;
        
        // Pointer to simulator utilities
        ExecutionManager* simulator;
        TraceManager* tracer;
        StatisticManager* stats;
    public:
        ISimulable(unsigned long id, char* name = NULL);
        static unsigned long getNextAvailableId();
        virtual void initCycle() = 0;
        virtual void printStatistics(ofstream* file);
        
        // Getters
        unsigned long getId();
        char* getName();
};

class ISimulableEvent: public IEventCallback{
    private:
        ISimulable* simulated;
        
    public:
        ISimulableEvent(EventName name, ISimulable* sim);
        void simulate();
};

#endif	/* ISIMULABLE_H */

