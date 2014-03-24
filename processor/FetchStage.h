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

class FetchStage : public PipelineStage{
    private:
        Queue<Instruction*>* fetchQueue;
        /* Pointer to the memory bus which connects to the 1st element in the
         * memory hierarchy. It's of the base type 'InterconnectionNetwork' for
         * configurability, but generally it'll be a bus. */
        InterconnectionNetwork* memoryBus;
        IssueStage* nextStage;
        int fetchQueueMaxSize;
        int fetchWidth;
        int decodeWidth;
        
        /* TODO: think of a more generic structure? -> by now its a 32 bit architecture (MIPS?) */
        unsigned int instructionPointer;
        
    public:
        FetchStage(InterconnectionNetwork* fetchNetwork);
        void pipeInstruction(Instruction*);
        void simulateStage(PipelineStage* retValue);
        void addIntructionToInstructionWindow(Instruction* inst);
};

#endif	/* FETCHSTAGE_H */

