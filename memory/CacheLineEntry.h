/* 
 * File:   CacheLineEntry.h
 * Author: fede
 *
 * Created on 4 de marzo de 2014, 04:40 PM
 */

#ifndef CACHELINEENTRY_H
#define	CACHELINEENTRY_H

enum CacheLineState{
    CACHE_LINE_INVALID,
    CACHE_LINE_MODIFIED,
    CACHE_LINE_EXCLUSIVE,
    CACHE_LINE_SHARED
};

class CacheLineEntry{
    // Object to represent a cache line
    private:
        // Line Status
        bool used;
        bool dirty;
        unsigned int tag;
        // Coherence Status Information
        CacheLineState state;
        
        // Line data
        unsigned int lineSize; // Size in bytes
        unsigned char* lineData;
        unsigned long timestamp; // Last time used, for LRU policy 
    public:
        CacheLineEntry(unsigned int ls):used(0),dirty(0),tag(0),lineSize(ls){
            lineData = new unsigned char[ls];
            state = CACHE_LINE_INVALID;
        };
        bool isUsed()   { 
            return used;  
        };
        bool isDirty()  { 
            return dirty; 
        };
        unsigned int getTag() { 
            return tag; 
        };
        unsigned int getLineSize(){
            return lineSize;
        };
        unsigned char* getLineData(){
            return lineData;
        };
        unsigned long getTimestamp(){
            return timestamp;   
        }
        CacheLineState getState(){
            return state;
        }
        void setLineData(unsigned char* data){
            // Todo: delete data?
            lineData = data;
        };
        void setUsed(bool u){ 
            used = u;  
        };
        void setDirty(bool d){ 
            dirty = d; 
        };        
        void setTag(unsigned int t) { 
            tag = t;
        }; 
        void setTimestamp(unsigned long t){
            timestamp = t;
        };
        void setCacheLineState(CacheLineState s){
            state = s;
        };
};

#endif	/* CACHELINEENTRY_H */

