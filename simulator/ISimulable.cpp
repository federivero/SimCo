#include "ISimulable.h"
#include "../exceptions/UnsuportedEventException.h"

ISimulable::ISimulable(unsigned long id, char* name){
    this->id = id;
    this->name = name;
    simulator = ExecutionManager::getInstance();
    tracer = TraceManager::getInstance();
    stats = StatisticManager::getInstance();
}

ISimulableEvent::ISimulableEvent(EventName name, ISimulable* sim):IEventCallback(name){
    simulated = sim;
}
        
void ISimulableEvent::simulate(){
    switch(eventName){
        case SIMULABLE_START_CYCLE:
            simulated->initCycle();
            break;
        default:
            throw new UnsuportedEventException("Illegal event for ISimulableEvent");
            break;
    }
}

void ISimulable::printStatistics(ofstream* file){
    if (name != NULL)
        *file << "Name " << name << endl;
}
unsigned long ISimulable::getId(){
    return id;
}

char* ISimulable::getName(){
    return name;
}

