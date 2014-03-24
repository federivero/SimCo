#include "ISimulable.h"
#include "../exceptions/UnsuportedEventException.h"

void ISimulableEvent::simulate(){
    switch(eventName){
        case SIMULABLE_START_CYCLE:
            
            break;
        default:
            throw new UnsuportedEventException("Illegal event for ISimulableEvent");
            break;
    }
}


