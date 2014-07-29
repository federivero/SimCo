/* 
 * File:   ComputationalSystem.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:48 AM
 */

#ifndef COMPUTATIONALSYSTEM_H
#define	COMPUTATIONALSYSTEM_H

class Processor;

class ComputationalSystem{
private:
    Processor** processors;
    int processorCount;
    // Keeps count of processors that have not ended execution
    int executingProcessors;
    
public:
    ComputationalSystem();

    /* Returns true if execution has finished */
    bool finishedExecution();
    
    /* Called by processors when they end execution */
    void markProcessorAsFinished();
    
    /* Access operations*/
    Processor** getProcessors();
    int getProcessorCount();
    /* Adds a processor to the computational system, with number 'processorNumber' */
    void addProcessor(Processor* processor, int processorNumber);
    void setProcessorCount(int processorCount);
};

#endif	/* COMPUTATIONALSYSTEM_H */

