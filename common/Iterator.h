/* 
 * File:   Iterator.h
 * Author: fede
 *
 * Created on 23 de marzo de 2014, 10:38 PM
 */

#ifndef ITERATOR_H
#define	ITERATOR_H

template <class T>
class Iterator{
    private:
        
    public:
        bool hasNext() = 0;
        T* next() = 0;
};

#endif	/* ITERATOR_H */

