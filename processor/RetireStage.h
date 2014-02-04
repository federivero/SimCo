/* 
 * File:   RetireStage.h
 * Author: fede
 *      
 * Created on 22 de enero de 2014, 02:02 PM
 */

#ifndef RETIRESTAGE_H
#define	RETIRESTAGE_H

#include "../common/Queue.h"
#include "../architecture/Instruction.h"

class RetireStage : public PipelineStage{
    private:
        Queue<Instruction*> rob;
        
        
        
    public:
        RetireStage();    
};

#endif	/* RETIRESTAGE_H */

