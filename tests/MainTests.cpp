
/* 
 * File:   MainTests.cpp
 * Author: fede
 *
 * Created on 22/01/2014, 05:15:53 PM
 */

#include <stdlib.h>
#include <iostream>

#include "memory/MemoryRequest.h"
#include "common/Stack.h"
#include "common/Map.h"
#include "exceptions/RuntimeException.h"
#include "memory/Cache.h"
#include "debug/MemoryDebug.h"

using namespace std;

/*
 * Simple C++ Test Suite
 */

void testStack() {
    MemoryRequest* m = new MemoryRequest(1000,10,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m2 = new MemoryRequest(1010,12,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m3 = new MemoryRequest(1020,14,MEMORY_REQUEST_MEMORY_READ);

    std::cout << "Stack test 1" << std::endl;
    Stack<MemoryRequest>* stack = new Stack<MemoryRequest>(3);
    stack->push(m);
    stack->push(m2);
    stack->push(m3);
    if (stack->isFull()){
        cout << "El stack está lleno! OK " << endl;
    }else{
        throw new RuntimeException("ERROR: El stack debería estar lleno!");
    }
    if (stack->exists(m2) != -1){
        cout << "OK! M2 pertenece al stack" << endl;
    }else{
        throw new RuntimeException("Error: M2 Pertenece al stack!");
    }
    cout << "Tamaño stack antes de remover un elemento: " << stack->getSize() << endl;
    stack->remove(0);
    cout << "Tamaño stack luego de remover un elemento: " << stack->getSize() << endl;
    cout << (stack->pop())->getMemoryAdress() << endl;
    cout << (stack->pop())->getMemoryAdress() << endl;
    if (stack->exists(m2) == -1){
        cout << "OK! M2 no pertenece al stack" << endl;
    }else{
        throw new RuntimeException("Error, M2 no pertenece al stack!");
    }
}

void mapTest(){
    MemoryRequest* m = new MemoryRequest(1000,10,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m2 = new MemoryRequest(1010,12,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m3 = new MemoryRequest(1020,14,MEMORY_REQUEST_MEMORY_READ);

    std::cout << "Map test 1" << std::endl;
    GenMap<MemoryRequest,int>* mmap = new ListMap<MemoryRequest,int>(3);
    int valor1 = 3;
    int valor2 = 4;
    int valor3 = 6;
    mmap->put(m,&valor1);
    mmap->put(m2,&valor2);
    mmap->put(m3,&valor3);
    if (mmap->isFull()){
        cout << "El mapa está lleno! OK " << endl;
    }else{
        throw new RuntimeException("ERROR: El mapa debería estar lleno!");
    }
    if (mmap->exists(m2) != -1){
        cout << "OK! M2 pertenece al mapa" << endl;
    }else{
        throw new RuntimeException("Error: M2 Pertenece al mapa!");
    }
    mmap->remove(m2);
    if (mmap->exists(m2) == -1){
        cout << "OK! M2 no pertenece al mapa" << endl;
    }else{
        throw new RuntimeException("Error, M2 no pertenece al mapa!");
    }
}

void cacheTest(){
    std::cout << "Cache test 1" << std::endl;
    MemoryDebug* mdeb = new MemoryDebug();
    Cache* c = new Cache(4,1,16);
    c->setReplacementPolicy(CACHE_REPLACEMENT_RANDOM);
    c->setWritePolicy(CACHE_WRITE_WRITEBACK);
    mdeb->printCacheStatus(c);
    MemoryRequest* req = new MemoryRequest(1145,4,MEMORY_REQUEST_MEMORY_WRITE);
    unsigned char* data = (unsigned char*) "hola";
    MemoryChunk* memChunk = new MemoryChunk(data,4);
    req->setRawData(memChunk);
    c->submitMemoryRequest(req,NULL);
    
    /*
    mdeb->printCacheStatus(c);
    MemoryResponse* resp = new MemoryResponse(2,MEMORY_REQUEST_MEMORY_READ, req);
    c->submitMemoryResponse(resp,NULL);
    mdeb->printCacheStatus(c);
     * */
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% DataStructure test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (testStack1)" << std::endl;
    
    testStack();
    
    std::cout << "%TEST_FINISHED% time=0 test1 (testStack1)" << std::endl;

   
    std::cout << "%TEST_STARTED% test2 (mapTest1)" << std::endl;
    
    mapTest();
    
    std::cout << "%TEST_FINISHED% time=0 test2 (testStack2)" << std::endl;
    
    std::cout << "%TEST_STARTED% test3 (CacheTest1)" << std::endl;
    
    cacheTest();
    
    std::cout << "%TEST_FINISHED% time=0 test3 (CacheTest1)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

