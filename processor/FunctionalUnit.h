/* 
 * File:   FunctionalUnit.h
 * Author: fede
 *
 * Created on 22 de enero de 2014, 02:04 PM
 */

#ifndef FUNCTIONALUNIT_H
#define	FUNCTIONALUNIT_H

#include "Register.h"
#include "../architecture/Instruction.h"
#include "../simulator/ISimulable.h"

enum FunctionalUnitType{
    FUNCTIONAL_UNIT_INT_ALU, FUNCTIONAL_UNIT_INT_MULTIPLIER,
    FUNCTIONAL_UNIT_FP_ALU, FUNCTIONAL_UNIT_FP_MULTIPLIER
};

class ExecuteStage;

class FunctionalUnit : public ISimulable{
    
    private:
        FunctionalUnitType type;
    protected:
        // Functional Unit latency in cycles
        int latency;
        
        // Data structure holding the resultvalue
        InstructionResult* instructionResult;
        
        // ExecuteStage managing this functionalUnit
        ExecuteStage* executionStage;
    public:
        FunctionalUnit(unsigned long id, char* name, FunctionalUnitType type, ExecuteStage* execStage, int latency);
        FunctionalUnitType getType();
    
        // Simulator operations
        virtual void initExecution();
        virtual void endExecution();
        
        virtual InstructionResult* getInstructionResult();
        
        // ISimulable operations 
        void initCycle();
        
        // Polymorphic function to determine if this functional unit is an ALU
        virtual bool isALU();
};

class FunctionalUnitEvent : public IEventCallback{
    private:
        FunctionalUnit* functionalUnit;
        
    public:
        FunctionalUnitEvent(EventName name, FunctionalUnit* funit);
        void simulate();
};

class ALU : public FunctionalUnit{
    private:

    protected:
        ALUFunction function;
        bool nFlag;
        bool zFlag;
        bool cFlag;
        bool vFlag;

    public:
        ALU(unsigned long id, char* name, FunctionalUnitType type, ExecuteStage* execStage, int latency);
        bool getNFlagValue();
        bool getZFlagValue();
        bool getCFlagValue();
        bool getVFlagValue();
        bool isALU();
};

class IntALU : public ALU{

    private:
        // TODO: Using 64 bit variables but could be of a more generic type (IntOperand?)
        long firstOperand;
        long secondOperand;        
    
    public:
        IntALU(unsigned long id, char* name, ExecuteStage* execStage, int latency);
        
        // Simulator operations
        void initExecution();
        void endExecution();
        
        // Access operations
        void setALUFunction(ALUFunction function);
        void setFirstOperand(long firstOperand);
        void setSecondOperand(long secondOperand);
        InstructionResult* getInstructionResult();
};


#endif	/* FUNCTIONALUNIT_H */

