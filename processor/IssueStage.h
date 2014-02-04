/* 
 * File:   IssueStage.h
 * Author: fede
 *
 * Created on 21 de enero de 2014, 06:38 PM
 */

#ifndef ISSUESTAGE_H
#define	ISSUESTAGE_H

#include "../common/Queue.h"
#include "IssueQueueEntry.h"
#include "PipelineStage.h"

class IssueStage : public PipelineStage{
    private:
        /* IssueQueue: Keeps instructions on hold as they wait for a 
         functional unit to free and its operands to be produced */
        Queue<IssueQueueEntry*> issueQueue;
        
        int issueQueueSize;
        int issueWidth;
        
        
    public:
            
};

#endif	/* ISSUESTAGE_H */

