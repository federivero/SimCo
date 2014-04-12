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
        Iterator<T>* iterator();
        void setFirst(ListNode<T>* f){
            first = f;
        }
};

template <class T>
class ListIterator: public Iterator<T>{
    private:
        ListNode<T>* current;
        ListNode<T>* lastIterated;
        ListNode<T>* lastIteratedPrevious;
        List<T>* list;
    public:
        ListIterator(List<T>* l, ListNode<T>* first){
            current = first;
            lastIterated = NULL;
            lastIteratedPrevious = NULL;
            list = l;
        }
        virtual bool hasNext(){
            return (current != NULL);
        }
        virtual T* next(){
            T* result = current->getData();
            lastIteratedPrevious = lastIterated;
            lastIterated = current;
            current = current->getNext();
            return result;
        }
        virtual void remove(){
            // LastIteratedPrevious != NULL -> there is a previous one
            if (lastIteratedPrevious != NULL){
                lastIteratedPrevious->setNext(current);
            }else{
                // If lastIteratedPrevious == NULL, the first element of the list is trying to be removed
                list->setFirst(current);
            }
            delete lastIterated;
            lastIterated = lastIteratedPrevious;
        }
};

template <class T>
Iterator<T>* List<T>::iterator(){
    Iterator<T>* result = new ListIterator<T>(this,first);
    return result;
}
    
#endif	/* LIST_H */

