/* 
 * File:   Queue.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:17 AM
 */

#ifndef QUEUE_H
#define	QUEUE_H

template <class T>
class Queue{
private:
    int size;
    int maxSize;
    T** array;
    int startIndex;
    int endIndex;
public:
    Queue(int s){
        maxSize = s;
        size = 0;
        startIndex = 0;
        endIndex = 0;
        array = new T*[maxSize];
    }
    bool isFull(){
        return (size == maxSize);
    }
    bool isEmpty(){
        return (size == 0);
    }
    int getSize(){
        return size;
    }
    int getMaxSize(){
        return maxSize;
    }
    /* PRE: size < maxsize*/
    void queue(T* elem){
        endIndex = (endIndex + 1) % maxSize;
        size++;
        array[endIndex] = elem;
    }
    /* PRE: size > 0*/
    T* dequeue(){
        T* retVal = array[startIndex];
        startIndex = (startIndex + 1) % maxSize;
        size--;
        return retVal;
    }
    
};

#endif	/* QUEUE_H */

