/* 
 * File:   GenericProcessor.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:05 AM
 */

#ifndef GENERICPROCESSOR_H
#define	GENERICPROCESSOR_H

#include "../interconnect/InterconnectionNetwork.h"
#include "PipelineStage.h"
#include "../architecture/ISA.h"

class InterconnectionNetwork;
class PipelineStage;

class Processor{
private:
    InterconnectionNetwork* network;
    PipelineStage* pipelineStages;
    ISA* instructionSetArchitecture;
    int pipelineStageCount;
public:
    Processor();
    void advanceClock(Processor* retValue);
    ISA* getISA();
    PipelineStage* getPipelineStage(int pipeStageNumber);
};

#endif	/* GENERICPROCESSOR_H */

