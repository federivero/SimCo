/* 
 * File:   Map.h
 * Author: fede
 *
 * Created on 12 de marzo de 2014, 08:39 PM
 */

#ifndef MAP_H
#define	MAP_H

#include <stdio.h>

template <class T, class U>
class GenMap{
private:
public:
    /* Inserts the pair <T,U> into the Map*/
    virtual void put(T key, U value) = 0;
    /* Given a T key, retuns a the U pair in the map, returns 0 otherwise */
    virtual U getData(T key) = 0;
    /* If theres a <T,U> pair in the map, returns its index, otherwise returns -1 */
    virtual int exists(T key) = 0;
    /* Returns true if the map is empty */
    virtual bool isEmpty() = 0;
    /* Returns true if the map is full */
    virtual bool isFull() = 0;
    /* Removes the value <T,U> from the Map, if it exists */
    virtual void remove(T key) = 0;
    /* Overrides the value U* of <T,U*>, with U, if the pair exists. Returns the old value of U */
    virtual U override(T key, U newValue) = 0;
};

template <class T, class U>
struct MapNode{
    T key;
    U value;
};


template <class T, class U>
class ListMap: public GenMap<T,U>{
    private:
        MapNode<T,U>* array;
        int maxSize;
        int endIndex;
    public:
        ListMap(int max){
            maxSize = max;
            array = new MapNode<T,U>[maxSize];
            endIndex = -1;
        }
        
        virtual U getData(T key){
            int index = exists(key);
            U retVal = 0;
            if (index != -1){
                retVal = array[index].value;
            }
            return retVal;
        }
        
        /* If key exists on the map, it returns its index. Otherwise returns -1 */
        virtual int exists(T key){
            int index = -1;
            for (int i = 0; i <= endIndex; i++){
                if (array[i].key == key){
                    index = i;
                    break;
                }
            }
            return index;
        }
        
        virtual void put(T key, U value){
            endIndex++;
            array[endIndex].key = key;
            array[endIndex].value = value;
        }
        
        virtual bool isEmpty(){
            return (endIndex == -1);
        }
        
        virtual bool isFull(){
            return (endIndex == (maxSize -1));
        }
        
        virtual void remove(T key){
            int index = exists(key);
            for (int i = index; i < endIndex; i++){
                array[i].key = array[i+1].key;
                array[i].value = array[i+1].value;
            }
            endIndex--;
        }
        
        virtual U override(T key, U newValue){
            int index = exists(key);
            U retVal = 0;
            if (index != -1){
                retVal = array[index].value;
                array[index].value = newValue;
            }
            return retVal;
        }
            
};
#endif	/* MAP_H */

