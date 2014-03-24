
/* 
 * File:   ConfigFileTest.cpp
 * Author: fede
 *
 * Created on 22/01/2014, 05:15:53 PM
 */

#include <stdlib.h>
#include <iostream>

#include "simulator/ConfigManager.h"
#include "memory/Cache.h"
#include "debug/MemoryDebug.h"
#include <exception>

using namespace std;

/*
 * Simple C++ Test Suite
 */

void testCache1() {
    try{
        std::cout << "Cache test 1" << std::endl;
        MemoryDebug* mdeb = new MemoryDebug();
        Cache* c = new Cache(4,2,16);
        mdeb->printCacheStatus(c);
        MemoryRequest* req = new MemoryRequest(2,4,MEMORY_REQUEST_MEMORY_WRITE);
        unsigned char* data = (unsigned char*) "hola";
        MemoryChunk* memChunk = new MemoryChunk(data,4);
        req->setRawData(memChunk);
        c->submitMemoryRequest(req,NULL);
        mdeb->printCacheStatus(c);
    }catch(exception e){
        cout << e.what() << endl;
    }
}



