/* 
 * File:   IssueQueueEntry.h
 * Author: fede
 *
 * Created on 22 de enero de 2014, 02:45 PM
 */

#ifndef ISSUEQUEUEENTRY_H
#define	ISSUEQUEUEENTRY_H

#include "Register.h"

class IssueQueueEntry{
private:
    Instruction* inst;
    bool speculative;
   
    /* An instrucction on IssueQueue is pending if there's an 
     operand that is yet to be produced */
    bool pending;
    
    bool destValid;
    Register* dest;
    
    bool src1Valid;
    Register* src1;
    
    bool src2Valid;
    Register* src2;
    
public:
    
    IssueQueueEntry();
    
};

#endif	/* ISSUEQUEUEENTRY_H */

