/* 
 * File:   ISimulable.h
 * Author: fede
 *
 * Created on 23 de marzo de 2014, 10:18 PM
 */

#ifndef ISIMULABLE_H
#define	ISIMULABLE_H

#include "IEventCallback.h"

class ISimulable{
    private:
    public:
        virtual void initCycle() = 0;
};

class ISimulableEvent: public IEventCallback{
    private:
        ISimulable* simulated;
        
    public:
        void simulate();
};

#endif	/* ISIMULABLE_H */

