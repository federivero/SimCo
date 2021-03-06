
#include "MemoryDebug.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void MemoryDebug::printCacheStatus(Cache* cache){
    unsigned int setCount = cache->getSetCount();
    unsigned int associativity = cache->getAssociativity();
    unsigned int lineSize = cache->getLineSize();
    cout << "Cache status:" << endl;
    cout << "Number of sets: " << setCount << endl;
    cout << "Associativity:  " << associativity << endl;
    cout << "Line Size:      " << lineSize << endl;
    cout << "Line content: " << endl;
    int lineCount = setCount * associativity;
    for (int i = 0; i < lineCount; i++){
        cout << "  Line " << i << ": ";
        if (cache->getCacheLine(i) == NULL){
            cout << " Empty";
        }else{
            cout << " TAG " << cache->getCacheLine(i)->getTag() << " Status: ";
            switch(cache->getCacheLine(i)->getState()){
                case CACHE_LINE_INVALID:
                    cout << "Invalid ";
                    break;
                case CACHE_LINE_MODIFIED:
                    cout << "Modified ";
                    break;
                case CACHE_LINE_SHARED:
                    cout << "Shared ";
                    break;
                case CACHE_LINE_EXCLUSIVE:
                    cout << "Exclusive ";
                    break;
                default:
                    break;
            }
                    
                    
            cout << " - Content: ";
            for (int j = 0; j < lineSize; j++) 
                cout << cache->getCacheLine(i)->getLineData()[j];
        }
        cout << endl;
    }
}       

