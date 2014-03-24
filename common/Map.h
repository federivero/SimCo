/* 
 * File:   Map.h
 * Author: fede
 *
 * Created on 12 de marzo de 2014, 08:39 PM
 */

#ifndef MAP_H
#define	MAP_H

template <class T, class U>
class GenMap{
private:
public:
    virtual U* getData(T* key) = 0;
    virtual int exists(T* key) = 0;
    virtual void put(T* key, U* value) = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void remove(T* key) = 0;
};

template <class T, class U>
struct MapNode{
    T* key;
    U* value;
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
        
        virtual U* getData(T* key){
            int index = exists(key);
            U* retVal = NULL;
            if (index != -1){
                retVal = array[index].value;
            }
            return retVal;
        }
        
        virtual int exists(T* key){
            int index = -1;
            for (int i = 0; i <= endIndex; i++){
                if (array[i].key == key){
                    index = i;
                    break;
                }
            }
            return index;
        }
        
        virtual void put(T* key, U* value){
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
        
        virtual void remove(T* key){
            int index = exists(key);
            for (int i = index; i < endIndex; i++){
                array[i].key = array[i+1].key;
                array[i].value = array[i+1].value;
            }
        }
            
};
#endif	/* MAP_H */

