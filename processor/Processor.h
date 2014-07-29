/* 
 * File:   GenericProcessor.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:05 AM
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

class ISA;
class RegisterFile;
class FetchStage;
class ExecuteStage;

#include "../simulator/ISimulable.h"

class Processor : public ISimulable{
private:
protected:
    /* Pointer to the computational system in the context of this processor */
    ComputationalSystem* compSystem;
    
    /* Pointer to implementation */
    FetchStage* fetchStage;
    ExecuteStage* executeStage;
    
    /* Pointer to register file */
    RegisterFile* architectedRegisterFile;
        
    // Pointer to the ISA being implemented
    ISA* instructionSetArchitecture;
    
    // Value of the PC register
    unsigned long PC;
    // Value of FLAGS Register
    bool zFlag;  // Zero Flag
    bool nFlag;  // Negative Flag
    bool cFlag;  // Carry Flag
    bool vFlag;  // Overflow Flag
    
    // Statistic variables
    unsigned long executedInstructions;
    unsigned long jumpInstructions;
    unsigned long aluInstructions;
    unsigned long memoryInstructions;
public:
    
    Processor();
    Processor(unsigned long id, char* name,ISA* isa);
    ISA* getISA();
    unsigned long getPCValue();
    void setPCValue(unsigned long newValue);
    
    /* Simulator Functions */
    
    // function called by the fetch stage when an instruction gets fetched succesfully
    virtual void instructionFetched(){};
    // function called by the execute stage when an instruction gets executed succesfully
    virtual void instructionExecuted(Instruction* inst){};
    
    virtual bool hasFinishedExecution() = 0;
    /* Function called by this processor when if finished execution */
    void finishedExecution();
    
    // Statistic function
    virtual void printStatistics(ofstream* file);
    
    virtual void scheduleInitExecutionEvent() = 0;
    
    // Control Functions 
    void setZFlagValue(bool newValue);
    void setNFlagValue(bool newValue);
    void setCFlagValue(bool newValue);
    void setVFlagValue(bool newValue);
    void setISA(ISA* isa);
    void setComputationalSystem(ComputationalSystem* compSys);
    
    // Access Functions
    FetchStage* getFetchStage();
    ExecuteStage* getExecuteStage();
    
};

#endif	/* GENERICPROCESSOR_H */

