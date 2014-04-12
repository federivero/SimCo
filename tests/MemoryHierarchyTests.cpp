/* 
 * File:   MemoryHierarchyTests.cpp
 * Author: fede
 *
 * Created on 29/03/2014, 04:12:35 PM
 */

#include <stdlib.h>
#include <iostream>

#include "simulator/ExecutionManager.h"
#include "memory/RAM.h"
#include "interconnect/InterconnectionNetwork.h"
#include "interconnect/Bus.h"
#include "simulator/TraceManager.h"
#include "debug/DummyDispatcher.h"
#include "exceptions/RuntimeException.h"
#include "exceptions/UnsuportedEventException.h"
#include "memory/Cache.h"
#include "debug/MemoryDebug.h"
#include "exceptions/UnalignedMemoryAccessException.h"
#include "simulator/StatisticManager.h"

/*
 * Simple C++ Test Suite
 */

void ramTests() {
    try{
        std::cout << "MemoryHierarchyTests - Ram Test" << std::endl;

        // Initialize tracer
        TraceManager* tracer = TraceManager::getInstance();
        tracer->setFileName((char*) "RAM.trace");
        tracer->setEnabled(true);
        tracer->startTrace();

        // Initialize simulator
        ExecutionManager* ex = ExecutionManager::getInstance();
        ex->initialize();
        ex->setUnlimitedCycles(false);
        ex->setCycleLimit(10);
        ComputationalSystem* compSys = new ComputationalSystem();
        ex->setComputationalSystem(compSys);

        DummyDispatcher* dummyDispatcher = new DummyDispatcher(3);

        // Initialize devices
        Bus* localBus = new Bus(1,2,2);
        MemoryDevice* ram = new RAM(2,1024,1,2,localBus);
        localBus->addDevice(ram,0); 
        localBus->addDevice(dummyDispatcher,1);

        ISimulableEvent* fixedEvent1 = new ISimulableEvent(SIMULABLE_START_CYCLE,localBus);
        ISimulableEvent* fixedEvent2 = new ISimulableEvent(SIMULABLE_START_CYCLE,ram);
        ex->addFixedEvent(fixedEvent1);
        ex->addFixedEvent(fixedEvent2);

        MemoryRequest* req = new MemoryRequest(0x1E8,10,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data = (unsigned char*) "write test";
        MemoryChunk* writeData = new MemoryChunk(data,10);
        req->setRawData(writeData);
        MemoryRequest* req2 = new MemoryRequest(0x1F8,17,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data2 = (unsigned char*) "second write test";
        MemoryChunk* writeData2 = new MemoryChunk(data2,17);
        req2->setRawData(writeData2);
        MemoryRequest* req3 = new MemoryRequest(0x1E0, 13, MEMORY_REQUEST_MEMORY_READ);
        
        dummyDispatcher->addMemoryRequest(req);
        dummyDispatcher->addMemoryRequest(req2);
        dummyDispatcher->addMemoryRequest(req3);
        
        // Initialize events
        //MemoryDeviceEvent* mde = MemoryDeviceEvent::createEvent(MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST,ram,req,localBus);
        //ex->addEvent(mde,1);
        InterconnectionNetworkEvent* ine = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                localBus,dummyDispatcher);
        ex->addEvent(ine,1);
        InterconnectionNetworkEvent* ine2 = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                localBus,dummyDispatcher);
        ex->addEvent(ine2,1);
        InterconnectionNetworkEvent* ine3 = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                localBus,dummyDispatcher);
        ex->addEvent(ine3,1);
        
        
        ex->simulate();

        tracer->finishTracing();
    }catch(RuntimeException* exception){
        cout << exception->what() << endl;
    }catch(UnsuportedEventException* exception){
        cout << exception->what() << endl;
    }catch(UnalignedMemoryAccessException* exception){
        cout << exception->what() << endl;
    }

}

void cacheAndRamTest(){
    try{
        std::cout << "MemoryHierarchyTests - Cache And Ram Test" << std::endl;

        // Initialize tracer
        TraceManager* tracer = TraceManager::getInstance();
        tracer->setFileName((char*) "CacheAndRam.trace");
        tracer->setEnabled(true);
        tracer->startTrace();

        // Initialize simulator
        ExecutionManager* ex = ExecutionManager::getInstance();
        ex->initialize();
        ex->setUnlimitedCycles(false);
        ex->setCycleLimit(20);
        ComputationalSystem* compSys = new ComputationalSystem();
        ex->setComputationalSystem(compSys);

        DummyDispatcher* dummyDispatcher = new DummyDispatcher(3);

        // Initialize devices
        Bus* CPUCacheBus = new Bus(1,2,1);
        Bus* cacheRAMBus = new Bus(2,2,1);
        MemoryDevice* ram = new RAM(3,1024,1,2,cacheRAMBus,(char*) "ram");
        Cache* cache = new Cache(4,8,2,16,1,1, (char*) "L1 Cache");
        tracer->traceNewBus(1);
        tracer->traceNewBus(2);
        tracer->traceNewRAM(3);
        tracer->traceNewCache(4);
        CPUCacheBus->addDevice(dummyDispatcher,0);
        CPUCacheBus->addDevice(cache,1); 
        cacheRAMBus->addDevice(cache,0);
        cacheRAMBus->addDevice(ram,1);
        cache->setUpperMemoryHierarchyPort(CPUCacheBus);
        cache->setLoweerMemoryHierarchyPort(cacheRAMBus);
        cache->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
        cache->setWritePolicy(CACHE_WRITE_WRITEBACK);
                
        ISimulableEvent* fixedEvent1 = new ISimulableEvent(SIMULABLE_START_CYCLE,CPUCacheBus);
        ISimulableEvent* fixedEvent2 = new ISimulableEvent(SIMULABLE_START_CYCLE,ram);
        ISimulableEvent* fixedEvent3 = new ISimulableEvent(SIMULABLE_START_CYCLE,cache);
        ISimulableEvent* fixedEvent4 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheRAMBus);
        ex->addFixedEvent(fixedEvent1);
        ex->addFixedEvent(fixedEvent2);
        ex->addFixedEvent(fixedEvent3);
        ex->addFixedEvent(fixedEvent4);

        MemorySystem* memSystem = new MemorySystem(NULL,2,1);
        memSystem->addMemoryDevice(cache,0);
        memSystem->addMemoryDevice(ram,1);
        StatisticManager* stats = StatisticManager::getInstance();
        stats->setMemorySystem(memSystem);
        
        // Compulsory miss
        MemoryRequest* req = new MemoryRequest(0x1E3,10,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data = (unsigned char*) "write test";
        MemoryChunk* writeData = new MemoryChunk(data,10);
        req->setRawData(writeData);
        // Compulsory Miss
        MemoryRequest* req2 = new MemoryRequest(0x1F2,11,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data2 = (unsigned char*) "second test";
        MemoryChunk* writeData2 = new MemoryChunk(data2,11);
        req2->setRawData(writeData2);
        // Read Hit
        MemoryRequest* req3 = new MemoryRequest(0x1E0, 13, MEMORY_REQUEST_MEMORY_READ);
        // Read Miss
        MemoryRequest* req4 = new MemoryRequest(0x3E4, 4, MEMORY_REQUEST_MEMORY_READ);
        // Write hit
        MemoryRequest* req5 = new MemoryRequest(0x1E8, 5, MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data3 = (unsigned char*) "third";
        MemoryChunk* writeData3 = new MemoryChunk(data3,5);
        req5->setRawData(writeData3);
        dummyDispatcher->addMemoryRequest(req);
        dummyDispatcher->addMemoryRequest(req2);
        dummyDispatcher->addMemoryRequest(req3);
        dummyDispatcher->addMemoryRequest(req4);
        dummyDispatcher->addMemoryRequest(req5);
        
       
        // Initialize events
        //MemoryDeviceEvent* mde = MemoryDeviceEvent::createEvent(MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST,ram,req,localBus);
        //ex->addEvent(mde,1);
        InterconnectionNetworkEvent* ine = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                CPUCacheBus,dummyDispatcher);
        ex->addEvent(ine,1);
        
        ex->simulate();
        
        MemoryDebug* md = new MemoryDebug();
        md->printCacheStatus(cache);

        tracer->finishTracing();
        stats->printStatistics((char*)"stats.txt");
    }catch(RuntimeException* exception){
        cout << exception->what() << endl;
    }catch(UnsuportedEventException* exception){
        cout << exception->what() << endl;
    }catch(UnalignedMemoryAccessException* exception){
        cout << exception->what() << endl;
    }    
}

void multilevelCacheTest(){
    try{
        std::cout << "MemoryHierarchyTests - MutilevelCache test" << std::endl;

        // Initialize tracer
        TraceManager* tracer = TraceManager::getInstance();
        tracer->setFileName((char*) "MultilevelCache.trace");
        tracer->setEnabled(true);
        tracer->startTrace();

        // Initialize simulator
        ExecutionManager* ex = ExecutionManager::getInstance();
        ex->initialize();
        ex->setUnlimitedCycles(false);
        ex->setCycleLimit(50);
        ComputationalSystem* compSys = new ComputationalSystem();
        ex->setComputationalSystem(compSys);

        DummyDispatcher* dummyDispatcher = new DummyDispatcher(3);

        // Initialize devices
        Bus* CPUCacheBus = new Bus(1,2,1);
        Bus* cacheRAMBus = new Bus(2,2,1);
        MemoryDevice* ram = new RAM(3,16384,1,2,cacheRAMBus,(char*) "ram"); // capacity 16 KB
        Cache* cacheL1 = new Cache(4,8,2,16,1,1, (char*) "L1 Cache");   // capacity 256 B
        Cache* cacheL2 = new Cache(5,16,4,64,1,1, (char*) "L2 Cache");  // capacity 4BB
        Bus* interCacheBus = new Bus(6,2,1);
        tracer->traceNewBus(1);
        tracer->traceNewBus(2);
        tracer->traceNewRAM(3);
        tracer->traceNewCache(4);
        tracer->traceNewCache(5);
        tracer->traceNewBus(6);
        CPUCacheBus->addDevice(dummyDispatcher,0);
        CPUCacheBus->addDevice(cacheL1,1);
        interCacheBus->addDevice(cacheL1,0);
        interCacheBus->addDevice(cacheL2,1);
        cacheRAMBus->addDevice(cacheL2,0);
        cacheRAMBus->addDevice(ram,1);
        cacheL1->setUpperMemoryHierarchyPort(CPUCacheBus);
        cacheL1->setLoweerMemoryHierarchyPort(interCacheBus);
        cacheL1->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
        cacheL1->setWritePolicy(CACHE_WRITE_WRITETHROUGH);
        
        cacheL2->setUpperMemoryHierarchyPort(interCacheBus);
        cacheL2->setLoweerMemoryHierarchyPort(cacheRAMBus);
        cacheL2->setReplacementPolicy(CACHE_REPLACEMENT_LRU);
        cacheL2->setWritePolicy(CACHE_WRITE_WRITEBACK);
                       
        ISimulableEvent* fixedEvent1 = new ISimulableEvent(SIMULABLE_START_CYCLE,CPUCacheBus);
        ISimulableEvent* fixedEvent2 = new ISimulableEvent(SIMULABLE_START_CYCLE,ram);
        ISimulableEvent* fixedEvent3 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheL1);
        ISimulableEvent* fixedEvent4 = new ISimulableEvent(SIMULABLE_START_CYCLE,cacheRAMBus);
        ISimulableEvent* fixedEvent5 = new ISimulableEvent(SIMULABLE_START_CYCLE,interCacheBus);
        ex->addFixedEvent(fixedEvent1);
        ex->addFixedEvent(fixedEvent2);
        ex->addFixedEvent(fixedEvent3);
        ex->addFixedEvent(fixedEvent4);
        ex->addFixedEvent(fixedEvent5);
        MemorySystem* memSystem = new MemorySystem(NULL,3,1);
        memSystem->addMemoryDevice(cacheL1,0);
        memSystem->addMemoryDevice(cacheL2,1);
        memSystem->addMemoryDevice(ram,2);
        StatisticManager* stats = StatisticManager::getInstance();
        stats->setMemorySystem(memSystem);
        
        // Compulsory miss
        MemoryRequest* req = new MemoryRequest(0x1E3,10,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data = (unsigned char*) "write test";
        MemoryChunk* writeData = new MemoryChunk(data,10);
        req->setRawData(writeData);
        // Compulsory Miss
        MemoryRequest* req2 = new MemoryRequest(0x1F2,11,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data2 = (unsigned char*) "second test";
        MemoryChunk* writeData2 = new MemoryChunk(data2,11);
        req2->setRawData(writeData2);
        // Read Hit
        MemoryRequest* req3 = new MemoryRequest(0x1E0, 13, MEMORY_REQUEST_MEMORY_READ);
        // Read Miss
        MemoryRequest* req4 = new MemoryRequest(0x3E4, 4, MEMORY_REQUEST_MEMORY_READ);
        // Write hit
        MemoryRequest* req5 = new MemoryRequest(0x1E8, 5, MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data3 = (unsigned char*) "third";
        MemoryChunk* writeData3 = new MemoryChunk(data3,5);
        req5->setRawData(writeData3);
        dummyDispatcher->addMemoryRequest(req);
        dummyDispatcher->addMemoryRequest(req2);
        dummyDispatcher->addMemoryRequest(req3);
        dummyDispatcher->addMemoryRequest(req4);
        dummyDispatcher->addMemoryRequest(req5);
        
       
        // Initialize events
        //MemoryDeviceEvent* mde = MemoryDeviceEvent::createEvent(MEMORY_DEVICE_SUBMIT_MEMORY_REQUEST,ram,req,localBus);
        //ex->addEvent(mde,1);
        InterconnectionNetworkEvent* ine = InterconnectionNetworkEvent::createEvent(INTERCONNECTION_NETWORK_EVENT_REQUEST_ACCESS,
                CPUCacheBus,dummyDispatcher);
        ex->addEvent(ine,1);
        
        ex->simulate();
        
        MemoryDebug* md = new MemoryDebug();
        md->printCacheStatus(cacheL1);
        md->printCacheStatus(cacheL2);

        tracer->finishTracing();
        stats->printStatistics((char*)"statsMultilevel.txt");
    }catch(RuntimeException* exception){
        cout << exception->what() << endl;
    }catch(UnsuportedEventException* exception){
        cout << exception->what() << endl;
    }catch(UnalignedMemoryAccessException* exception){
        cout << exception->what() << endl;
    }    
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% MemoryHierarchyTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% ramTests (MemoryHierarchyTests)" << std::endl;
    ramTests();
    std::cout << "%TEST_FINISHED% time=0 ramTests (MemoryHierarchyTests)" << std::endl;

    std::cout << "%TEST_STARTED% CacheAndRamTest (MemoryHierarchyTests)\n" << std::endl;
    
    //cacheAndRamTest();
    
    std::cout << "%TEST_FINISHED% time=0 CacheAndRamTest (MemoryHierarchyTests)" << std::endl;
    
    std::cout << "%TEST_STARTED% MultilevelCacheTest (MemoryHierarchyTests)\n" << std::endl;
    
    multilevelCacheTest();
    
    std::cout << "%TEST_FINISHED% time=0 MultilevelCacheTest (MemoryHierarchyTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

