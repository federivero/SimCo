/* 
 * File:   FetchStage.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:15 AM
 */

#ifndef FETCHSTAGE_H
#define	FETCHSTAGE_H

#include "../interconnect/InterconnectionNetwork.h"
#include "../common/Queue.h"
#include "../simulator/ConfigManager.h"
#include "PipelineStage.h"
#include "IssueStage.h"

class FetchStage : public IMessageDispatcher{
    private:
        // Pointer to the processor containing this FetchStage
        Processor* processor;
        
        // Instruction Fetch Queue variables. Instructions Queued contains the value seen
        // by other cpu parts during cycle, since fetchQueue 
        Queue<Instruction*>* fetchQueue;
        int instructionsQueued;
        int cycleFetchedInstrutions;
        
        /* Pointer to the memory bus which connects to the 1st element in the
         * instruction memory hierarchy. */
        InterconnectionNetwork* instructionMemoryInterface;
        int fetchQueueMaxSize;
        int fetchWidth;
        int decodeWidth;
        
    public:
        FetchStage(unsigned long id, char* name, Processor* processor, InterconnectionNetwork* instructionMemoryInterface, int instructionFetchQueueSize);
        void accessGranted(InterconnectionNetwork* port);
        void submitMessage(Message* message, InterconnectionNetwork* port);
        
        /* Trigger function to fetch an instruction */
        void doFetch();
        
        /* ISimulable operations */
        void initCycle();
        
        // Getters 
        int getInstructionFetchQueueSize();
        Instruction* getNextInstructionFetched();
        
        //void pipeInstruction(Instruction*);
        //void simulateStage(PipelineStage* retValue);
        //void addIntructionToInstructionWindow(Instruction* inst);
};

#endif	/* FETCHSTAGE_H */

