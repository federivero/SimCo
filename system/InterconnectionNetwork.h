/* 
 * File:   InterconnectionNetwork.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 09:49 AM
 */

#ifndef INTERCONNECTIONNETWORK_H
#define	INTERCONNECTIONNETWORK_H

#include "ComputationalSystem.h"
#include "../memory/MemoryRequest.h"
#include "../memory/MemoryResponse.h"


class ComputationalSystem;

class InterconnectionNetwork{
private:
    ComputationalSystem* system;
public:
    MemoryResponse* getAdress(MemoryRequest* adress);
};

#endif	/* INTERCONNECTIONNETWORK_H */

