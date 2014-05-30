
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
#include "common/List.h"
#include "memory/MemoryTable.h"

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

void testQueue() {
    MemoryRequest* m = new MemoryRequest(1000,10,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m2 = new MemoryRequest(1010,12,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m3 = new MemoryRequest(1020,14,MEMORY_REQUEST_MEMORY_READ);

    std::cout << "Queue test 1" << std::endl;
    Queue<MemoryRequest*>* queue = new Queue<MemoryRequest*>(3);
    queue->queue(m);
    queue->queue(m2);
    queue->queue(m3);
    if (queue->isFull()){
        cout << "La cola está llena! OK " << endl;
    }else{
        throw new RuntimeException("ERROR: La cola debería estar llena!");
    }
    MemoryRequest* ret = queue->dequeue();
    if (ret->getMemoryAdress() != 1000){
        throw new RuntimeException("ERROR: Mensaje incorrecto!");
    }else{
        cout << "Ok: Mensaje correcto" << endl;
    }
}

void mapTest(){
    MemoryRequest* m = new MemoryRequest(1000,10,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m2 = new MemoryRequest(1010,12,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m3 = new MemoryRequest(1020,14,MEMORY_REQUEST_MEMORY_READ);

    std::cout << "Map test 1" << std::endl;
    GenMap<MemoryRequest*,int>* mmap = new ListMap<MemoryRequest*,int>(3);
    int valor1 = 3;
    int valor2 = 4;
    int valor3 = 6;
    mmap->put(m,valor1);
    mmap->put(m2,valor2);
    mmap->put(m3,valor3);
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
        throw new RuntimeException("Error, M2 pertenece al mapa y no debería!");
    }
}

void listTest(){
    MemoryRequest* m = new MemoryRequest(1000,10,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m2 = new MemoryRequest(1010,12,MEMORY_REQUEST_MEMORY_READ);
    MemoryRequest* m3 = new MemoryRequest(1020,14,MEMORY_REQUEST_MEMORY_READ);

    std::cout << "List test 1" << std::endl;
    List<MemoryRequest> *lista = new List<MemoryRequest>();
    lista->add(m);
    lista->add(m2);
    lista->add(m3);
    if (lista->exists(m2)){
        cout << "Ok! M2 pertenece a la lista" << endl;
    }else{
        throw new RuntimeException("Error: M2 no pertenece a la lista");
    }
    if (lista->isEmpty()){
        throw new RuntimeException("Error: La lista no debería ser vacía!");
    }else{
        cout << "Ok: la lista es vacía!" << endl;
    }
    cout << "Prueba de iteratod" << endl;
    int count = 0;
    Iterator<MemoryRequest> *it = lista->iterator();
    while(it->hasNext()){
        cout << it->next()->getMemoryAdress() << endl;
        count++;
    }
    if (count == 3){
        cout << "Ok! 3 elementos recorridos en al lista" << endl;
    }else{
        throw new RuntimeException("Iteración por un número incorrecto de eleemntos de la lista");
    }
 
    cout << "Test remover algún elemento en la iteración " << endl;
    it = lista->iterator();
    count = 1;
    while (it->hasNext()){
        cout << it->next()->getMemoryAdress() << endl;
        it->remove();
    }
    it = lista->iterator();
    while(it->hasNext()){
        cout << it->next()->getMemoryAdress() << endl;
    }
    cout << "Test OK" << endl;
    
    
}

void cacheTest(){
    std::cout << "Cache test 1" << std::endl;
    MemoryDebug* mdeb = new MemoryDebug();
    Cache* c = new Cache(1,4,1,16,1,1);
    c->setReplacementPolicy(CACHE_REPLACEMENT_RANDOM);
    c->setWritePolicy(CACHE_WRITE_WRITEBACK);
    mdeb->printCacheStatus(c);
    /*
    MemoryRequest* req = new MemoryRequest(1145,4,MEMORY_REQUEST_MEMORY_WRITE);
    unsigned char* data = (unsigned char*) "hola";
    MemoryChunk* memChunk = new MemoryChunk(data,4);
    req->setRawData(memChunk);
    c->submitMemoryRequest(req,NULL);
    */
    /*
    mdeb->printCacheStatus(c);
    MemoryResponse* resp = new MemoryResponse(2,MEMORY_REQUEST_MEMORY_READ, req);
    c->submitMemoryResponse(resp,NULL);
    mdeb->printCacheStatus(c);
     * */
}

void memoryTableTest1(){
    std::cout << "Memory Table Test 1 " << endl;
    cout << "Test single memory array" << endl;
    BaseMultilevelMemoryTable* b = new BaseMultilevelMemoryTable(100,1);
    unsigned char* rawData = new unsigned char[10];
    rawData = (unsigned char*) "holaquetal";
    MemoryChunk* c = new MemoryChunk(rawData,10);
    b->setMemoryContent(35,c);
    MemoryChunk* d = new MemoryChunk(rawData,10);
    b->setMemoryContent(48,d);
    MemoryChunk* c2 = b->getMemoryContent(39,16);
    cout << "Test for memory contents " << endl;
    c2->print();
    MemoryChunk* c3 = b->getMemoryContent(1,50);
    cout << "Test 2 for memory contents " << endl;
    c3->print();
    
    cout << "Test multilevel memory Table" << endl;
    if (isPowerOf2(2048)){
        cout << "Ok, 2048 es potencia de 2!! " << endl;
    }else{
        cout << "Error: 2048 es potencia de 2!! " << endl;
    }
    MultilevelMemoryTable* table = new MiddleMultilevelMemoryTable(512,2);
    table->setMemoryContent(0x132,c);
    MemoryChunk* c4 = table->getMemoryContent(0x132,10);
    cout << "Contenidos de memoria de dir 0x132 (debería ser 'holaquet')" << endl;
    c4->print();
    cout << "fin de contenido" << endl;
    cout << "Escribo en dirección 0x13B el valor 'holaquetal' " << endl;
    table->setMemoryContent(0x13B,c);
    table->setMemoryContent(0x148,c);
    c4 = table->getMemoryContent(0x13A,9);
    cout << "Contenidos de memoria de dir 0x13A (debería ser 'aholaquet')" << endl;
    c4->print();
    cout << "fin de contenido" << endl;
    c4 = table->getMemoryContent(0x140,20);
    cout << "Contenidos de memoria de dir 0x140 (debería ser 'uetal   holaquetal  ')" << endl;
    c4->print();
    cout << "fin de contenido" << endl; 
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% DataStructure test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testStack (testStack1)" << std::endl;
    
    testStack();
    
    std::cout << "%TEST_FINISHED% time=0 testStack (testStack1)" << std::endl;

     std::cout << "%TEST_STARTED% testQueue (testStack1)" << std::endl;
    
    testQueue();
    
    std::cout << "%TEST_FINISHED% time=0 testQueue (testStack1)" << std::endl;

   
    std::cout << "%TEST_STARTED% test2 (mapTest1)" << std::endl;
    
    mapTest();
    
    std::cout << "%TEST_FINISHED% time=0 test2 (mapTest1)" << std::endl;
    
    std::cout << "%TEST_STARTED% test3 (ListTest1)" << std::endl;    
    listTest();
    std::cout << "%TEST_FINISHED% time=0 test3 (ListTest1)" << std::endl;

    std::cout << "%TEST_STARTED% test4 (CacheTest1)" << std::endl;    
    cacheTest();
    std::cout << "%TEST_FINISHED% time=0 test4 (CacheTest1)" << std::endl;

    std::cout << "%TEST_STARTED% test5 (MemoryTableTest)" << std::endl;    
    memoryTableTest1();
    std::cout << "%TEST_FINISHED% time=0 test5 (MemoryTableTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

