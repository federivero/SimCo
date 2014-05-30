/* 
 * File:   P2PLink.h
 * Author: fede
 *
 * Created on 14 de abril de 2014, 06:04 PM
 */

#ifndef P2PLINK_H
#define	P2PLINK_H

#include "../memory/IMessageDispatcher.h"
#include "Message.h"

class P2PLink: public InterconnectionNetwork{
    // A point to point link sends messages between two attached dispatchers. 
    private:
        IMessageDispatcher* firstPoint;
        IMessageDispatcher* secondPoint;
        
    public:
        P2PLink(unsigned long id, IMessageDispatcher* firstPoint, IMessageDispatcher* secondPoint);
        virtual void requestAccess(IMessageDispatcher* requester);
        virtual void submitMessage(Message* message, IMessageDispatcher* submitter);
        
};

#endif	/* P2PLINK_H */

