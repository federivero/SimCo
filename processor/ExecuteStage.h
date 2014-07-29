/* 
 * File:   ExecuteStage.h
 * Author: fede
 *
 * Created on 22 de enero de 2014, 02:01 PM
 */

#ifndef EXECUTESTAGE_H
#define	EXECUTESTAGE_H

#include "../simulator/ISimulable.h"
#include "../architecture/Operand.h"
#include "FunctionalUnit.h"
#include "../common/Queue.h"
#include "../common/Map.h"

class Instruction;
class Processor;
class InterconnectionNetwork;

class ExecuteStage : public ISimulable{
    private:
        // Pointer to processor 
        Processor* processor;
        
        // Variables to control used functionalunits
        int integerAluCount;
        IntALU** integerAluFUnits;
        Queue<IntALU*> *availableIntegerAluFUnits;
        
        int integerMultiplierCount;
        FunctionalUnit** integerMultiplierFUnits;
        Queue<FunctionalUnit*> *availableIntegerMultiplierFUnits;
        
        int fpAluCount;
        FunctionalUnit** fpAluFUnits;
        Queue<FunctionalUnit*> *availableFpAluFUnits;
        
        int fpMultiplierCount;
        FunctionalUnit** fpMultiplierFUnits;
        Queue<FunctionalUnit*> *availableFpMultiplierFUnits;
        
        int loadStoreUnitCount;
        LoadStoreUnit** loadStoreFunctionalUnits;
        Queue<LoadStoreUnit*> *availableLoadStoreUnits;
        
        // Queue to hold Functional Units the cycle they end execution
        Queue<FunctionalUnit*> *releasedFunctionalUnits;
        // Mapping of functional units and instructions
        GenMap<FunctionalUnit*,Instruction*> *instructionMapping;
    public:
        ExecuteStage(Processor* processor, int intAluCount, int intAluLatency, int intMultiplierCount, int intMultiplierLatency, 
                int fpAluCount, int fpAluLatency, int fpMultiplierCount, int fpMultiplierLatency, int loadStoreUnitCount, InterconnectionNetwork* dataMemoryInterface);
        
        ExecuteStage(unsigned long id, char* name, Processor* processor, int intAluCount, int intAluLatency, int intMultiplierCount, int intMultiplierLatency, 
                int fpAluCount, int fpAluLatency, int fpMultiplierCount, int fpMultiplierLatency, int loadStoreUnitCount, InterconnectionNetwork* dataMemoryInterface);
        
        void initializeFunctionalUnits(int intAluCount, int intAluLatency, int intMultiplierCount, 
                int intMultiplierLatency, int fpAluCount, int fpAluLatency, int fpMultiplierCount,
                int fpMultiplierLatency, int loadStoreUnitCount, InterconnectionNetwork* dataMemoryInterface);
        
        void executeInstruction(Instruction* instruction);
        
        // Function called by a functional unit when it finishes execution
        void finishedExecution(FunctionalUnit* funit);
        
        // ISimulable Operations
        void initCycle();
        
        // Data memory interface setter
        void setDataMemoryInteface(InterconnectionNetwork* interface);
        
        Processor* getProcessor();
        LoadStoreUnit** getLoadStoreUnits();
        int getLoadStoreUnitCount();
};

#endif	/* EXECUTESTAGE_H */

