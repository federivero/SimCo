/* 
 * File:   MemoryTable.h
 * Author: fede
 *
 * Created on 26 de marzo de 2014, 01:54 PM
 */

#ifndef MEMORYTABLE_H
#define	MEMORYTABLE_H

#include "MemoryChunk.h"

// A memory table works as a 'dumb' memory.
class MemoryTable{
    private:
    

    protected:
        // MemoryTable capacity in bytes
        unsigned long capacity;
        // Base log 2 of capacity, used on every access
        unsigned int log2cap;
    public:
        MemoryTable(unsigned long cap);
        virtual MemoryChunk* getMemoryContent(unsigned int address, unsigned int size) = 0;
        virtual void setMemoryContent(unsigned int address, MemoryChunk* data) = 0;
};

// A MultilevelMemoryTable is a table that is saved as a tree, where the leaves have the data
class MultilevelMemoryTable: public MemoryTable{
    protected:
        int levelCount;
    public:
        static MultilevelMemoryTable* createMultilevelMemoryTable(unsigned long capacity, int levels);
        MultilevelMemoryTable(unsigned long cap, int levels);
};

// BaseMultilevelMemoryTables are the leves in the tree view of the table
class BaseMultilevelMemoryTable: public MultilevelMemoryTable{
    private:
        MemoryChunk* dataArray;
    public:
        BaseMultilevelMemoryTable(unsigned long capacity, int levels);
        virtual MemoryChunk* getMemoryContent(unsigned int address, unsigned int size);
        virtual void setMemoryContent(unsigned int address, MemoryChunk* data);
};

// MiddleMultilevelMemoryTables are the inner nodes in the tree view of the table
class MiddleMultilevelMemoryTable: public MultilevelMemoryTable{
    private:
        MultilevelMemoryTable** indexes;
        int indexLength;
        // Calculated values for faster memory access
        unsigned long lowerLevelCapacity;
    public:
        MiddleMultilevelMemoryTable(unsigned long capacity,int levels);
        virtual MemoryChunk* getMemoryContent(unsigned int address, unsigned int size);
        virtual void setMemoryContent(unsigned int address, MemoryChunk* data);
};

#endif	/* MEMORYTABLE_H */

