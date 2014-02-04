/* 
 * File:   ExecuteStage.h
 * Author: fede
 *
 * Created on 22 de enero de 2014, 02:01 PM
 */

#ifndef EXECUTESTAGE_H
#define	EXECUTESTAGE_H

#include "RetireStage.h"

class ExecuteStage : public PipelineStage{
    private:
        RetireStage*  nextStage;
        FunctionalUnit* functionalUnits;
    public:
        
            
};

#endif	/* EXECUTESTAGE_H */

