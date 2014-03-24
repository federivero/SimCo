/* 
 * File:   Stack.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 10:17 AM
 */

#ifndef STACK_H
#define	STACK_H

template <class T>
class Stack{
private:
    int size;
    int maxSize;
    T** array;
    int endIndex;
public:
    Stack(int s){
        maxSize = s;
        size = 0;
        endIndex = -1;
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
    void push(T* elem){
        endIndex = (endIndex + 1) % maxSize;
        size++;
        array[endIndex] = elem;
    }
    /* PRE: size > 0*/
    T* pop(){
        T* retVal = array[endIndex];
        endIndex = (endIndex - 1);
        size--;
        return retVal;
    }
    
    /* Aditional Operations */
    
    // Returns the index of the element in the structure
    int exists(T* elem){
        int index = -1;
        int j = 0;
        while ((index == -1) && (j <= endIndex)){
            if (array[j] == elem){
                index = j;
                break;
            }
            j = (j + 1); 
        }
        return index;
    }
    
    // Removes the element at index 'index' 
    void remove(int index){
        if (index <= endIndex){
            for (int i = index; i < endIndex; i++){
                array[i] = array[i+1];
            }
            endIndex--;
            size--;
        }
    }
};

#endif	/* STACK_H */

