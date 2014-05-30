/* 
 * File:   PipelineStage.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:47 AM
 */

#ifndef PIPELINESTAGE_H
#define	PIPELINESTAGE_H

#include "../architecture/Instruction.h"
#include "Processor.h"

class Instruction;
class Processor;
        
class PipelineStage{
private:
protected:
    Processor* processor;
public:
    //virtual void pipeInstruction(Instruction*) = 0;
    //virtual void simulateStage(PipelineStage* retValue) = 0;
};

#endif	/* PIPELINESTAGE_H */

