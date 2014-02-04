/* 
 * File:   ExecutionManager.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 11:48 AM
 */

#ifndef EXECUTIONMANAGER_H
#define	EXECUTIONMANAGER_H

#include "../system/ComputationalSystem.h"

class ExecutionManager{
private:
    /* Pointer to computational system described in the configuration.
     Simulation is implemented as two computational systems (see documentation)*/
    ComputationalSystem* currentExecution;
    ComputationalSystem* nextClockExecution;
    
public:
    ExecutionManager();
    void execute();
};

#endif	/* EXECUTIONMANAGER_H */

