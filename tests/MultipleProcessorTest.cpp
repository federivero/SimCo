/* 
 * File:   newsimpletest.cpp
 * Author: fede
 *
 * Created on 12/04/2014, 11:46:54 AM
 */

#include <stdlib.h>
#include <iostream>
#include "debug/DummyDispatcher.h"
#include "debug/MemoryDebug.h"
#include "memory/Cache.h"
#include "memory/RAM.h"
#include "interconnect/Bus.h"
#include "exceptions/RuntimeException.h"
#include "exceptions/UnsuportedEventException.h"
#include "exceptions/UnalignedMemoryAccessException.h"

using namespace std;

void twoDispatchersCoherenceTest(){
    try{
        std::cout << "MultipleProcessorTest - Two Dispatchers Coherence Test" << std::endl;

        // Initialize tracer
        TraceManager* tracer = TraceManager::getInstance();
        tracer->setFileName((char*) "TwoDispatchersCoherenceTest.trace");
        tracer->setEnabled(true);
        tracer->startTrace();

        // Initialize simulator
        ExecutionManager* ex = ExecutionManager::getInstance();
        ex->initialize();
        ex->setUnlimitedCycles(false);
        ex->setCycleLimit(100);
        ComputationalSystem* compSys = new ComputationalSystem();
        ex->setComputationalSystem(compSys);

        DummyDispatcher* dummyDispatcherOne = new DummyDispatcher(1);
        DummyDispatcher* dummyDispatcherTwo = new DummyDispatcher(2);
        
        // Initialize devices
        Bus* cpuOneCacheOneBus = new Bus(3,(char*)"cpuOneCacheOneBus",2,1);
        Bus* cpuTwoCacheTwoBus = new Bus(4,(char*)"cpuTwoCacheTwoBus",2,1);
        Bus* cacheOneTwoRAMBus = new Bus(5,(char*)"cacheOneTwoRAMBus",3,1);
        Cache* cacheOne = new Cache(6,8,2,16,1,1, (char*) "CPU 1 L1 Cache");
        Cache* cacheTwo = new Cache(7,8,2,16,1,1, (char*) "CPU 2 L1 Cache");
        MemoryDevice* ram = new RAM(3,1 << 10,1,2,cacheOneTwoRAMBus,(char*) "RAM");
        tracer->traceNewBus(cpuOneCacheOneBus);
        tracer->traceNewBus(cpuTwoCacheTwoBus);
        tracer->traceNewBus(cacheOneTwoRAMBus);
        tracer->traceNewCache(cacheOne);
        tracer->traceNewCache(cacheTwo);
        tracer->traceNewRAM(8);
        cpuOneCacheOneBus->addDevice(dummyDispatcherOne,0);
        cpuOneCacheOneBus->addDevice(cacheOne,1);
        
        cpuTwoCacheTwoBus->addDevice(dummyDispatcherTwo,0);
        cpuTwoCacheTwoBus->addDevice(cacheTwo,1);
        
        cacheOneTwoRAMBus->addDevice(cacheOne,0);
        cacheOneTwoRAMBus->addDevice(cacheTwo,1);
        cacheOneTwoRAMBus->addDevice(ram,2);
        
        cacheOne->setUpperMemoryHierarchyPort(cpuOneCacheOneBus);
        cacheOne->setLowerMemoryHierarchyPort(cacheOneTwoRAMBus);
        cacheOne->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
        cacheOne->setWritePolicy(CACHE_WRITE_WRITEBACK);
        cacheOne->setCoherenceProtocol(CACHE_COHERENCE_MSI);
        
        cacheTwo->setUpperMemoryHierarchyPort(cpuTwoCacheTwoBus);
        cacheTwo->setLowerMemoryHierarchyPort(cacheOneTwoRAMBus);
        cacheTwo->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
        cacheTwo->setWritePolicy(CACHE_WRITE_WRITEBACK);
        cacheTwo->setCoherenceProtocol(CACHE_COHERENCE_MSI);
                
        dummyDispatcherOne->setInterface(cpuOneCacheOneBus);
        dummyDispatcherTwo->setInterface(cpuTwoCacheTwoBus);
        
        ISimulableEvent* fixedEvent1 = new ISimulableEvent(SIMULABLE_START_CYCLE,cpuOneCacheOneBus);
        ISimulableEvent* fixedEvent2 = new ISimulableEvent(SIMULABLE_START_CYCLE,cpuTwoCacheTwoBus);
        ISimulableEvent* fixedEvent3 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheOneTwoRAMBus);
        ISimulableEvent* fixedEvent4 = new ISimulableEvent(SIMULABLE_START_CYCLE,dummyDispatcherOne);
        ISimulableEvent* fixedEvent5 = new ISimulableEvent(SIMULABLE_START_CYCLE,dummyDispatcherTwo);
        ISimulableEvent* fixedEvent6 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheOne);
        ISimulableEvent* fixedEvent7 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheTwo);
        ISimulableEvent* fixedEvent8 = new ISimulableEvent(SIMULABLE_START_CYCLE,ram);
        ex->addFixedEvent(fixedEvent1);
        ex->addFixedEvent(fixedEvent2);
        ex->addFixedEvent(fixedEvent3);
        ex->addFixedEvent(fixedEvent4);
        ex->addFixedEvent(fixedEvent5);
        ex->addFixedEvent(fixedEvent6);
        ex->addFixedEvent(fixedEvent7);
        ex->addFixedEvent(fixedEvent8);
        
        MemorySystem* memSystem = new MemorySystem(NULL,3,1);
        memSystem->addMemoryDevice(cacheOne,0);
        memSystem->addMemoryDevice(cacheTwo,1);
        memSystem->addMemoryDevice(ram,2);
        StatisticManager* stats = StatisticManager::getInstance();
        stats->setMemorySystem(memSystem);
        
        // Set values for test
        MemoryRequest* req = new MemoryRequest(0x030,16,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data = (unsigned char*) "coherence test 1";
        MemoryChunk* writeData = new MemoryChunk(data,16);
        req->setRawData(writeData);
        dummyDispatcherOne->queueMemoryRequest(req,1);
            
        // Set values for test
        MemoryRequest* req2 = new MemoryRequest(0x035,9,MEMORY_REQUEST_MEMORY_READ);
        dummyDispatcherTwo->queueMemoryRequest(req2,5);
           
        // Set values for test 
        MemoryRequest* req3 = new MemoryRequest(0x039,5,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data3 = (unsigned char*) "write";
        MemoryChunk* writeData3 = new MemoryChunk(data3,5);
        req3->setRawData(writeData3); 
        dummyDispatcherOne->queueMemoryRequest(req3,10);
        
        // Set values for test
        MemoryRequest* req4 = new MemoryRequest(0x030,16,MEMORY_REQUEST_MEMORY_READ);
        dummyDispatcherTwo->queueMemoryRequest(req4,15); 
        
        // Set values for test
        MemoryRequest* req5 = new MemoryRequest(0x130,13,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data5 = (unsigned char*) "modified test";
        MemoryChunk* writeData5 = new MemoryChunk(data5,13);
        req5->setRawData(writeData5);
        dummyDispatcherTwo->queueMemoryRequest(req5,20);
        
        ex->simulate();
        
        MemoryDebug* md = new MemoryDebug();
        md->printCacheStatus(cacheOne);
        md->printCacheStatus(cacheTwo);
        
        tracer->finishTracing();
        stats->printStatistics((char*)"TwoCPUAmdCacheStats.txt");
    }catch(RuntimeException* exception){
        cout << exception->what() << endl;
    }catch(UnsuportedEventException* exception){
        cout << exception->what() << endl;
    }catch(UnalignedMemoryAccessException* exception){
        cout << exception->what() << endl;
    }    
}



int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% MultipleProcessorTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% TwoCPUOwnCaches (MultipleProcessorTe)" << std::endl;

    twoDispatchersCoherenceTest();
    
    std::cout << "%TEST_FINISHED% time=0 TwoCPUOwnCaches (MultipleProcessorTest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (MultipleProcessorTest)\n" << std::endl;

    std::cout << "%TEST_FINISHED% time=0 test2 (MultipleProcessorTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

