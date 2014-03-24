/* 
 * File:   List.h
 * Author: fede
 *
 * Created on 23 de marzo de 2014, 10:37 PM
 */

#ifndef LIST_H
#define	LIST_H

#include "Iterator.h"
#include "stdio.h"

template <class T>
class ListNode{
    private:
        ListNode* next;
        T* data;
    public:
        ListNode<T>* getNext(){
            return next;
        }
        T* getData(){
            return data;
        }
        void setData(T* d){
            data = d;
        }
        void setNext(ListNode* n){
            next = n;
        }
};

template <class T>
class ListIterator: public Iterator<T>{
    private:
        ListNode<T>* current;
        
    public:
        ListIterator(ListNode<T>* first){
            current = first;
        }
        virtual bool hasNext(){
            return (current != NULL);
        }
        virtual T* next(){
            T* result = current->getData();
            current = current->getNext();
            return result;
        }
};

template <class T>
class List{
    private:
        ListNode<T>* first;
        int size;
    public:
        List(){
            size = 0;
            first = NULL;
        }
        
        void add(T* element){
            ListNode<T>* n = new ListNode<T>();
            n->setNext(first);
            n->setData(element);
            first = n;
            size++;
        }
        bool exists(T* element){
            ListNode<T>* aux = first;
            bool result = false;
            while (aux != NULL){
                if (aux->getData() == element){
                    result = true;
                    break;
                }
                aux = aux->getNext();
            }
            return result;
        }
        bool isEmpty(){
            return (size == 0);
        }
        int getSize(){
            return size;
        }
        Iterator<T>* iterator(){
            Iterator<T>* result = new ListIterator<T>(first);
            return result;
        }
};


#endif	/* LIST_H */

