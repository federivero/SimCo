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
        // Returns true if next call to 'next' will return a non-null value
        virtual bool hasNext() = 0;
        // Returns next element in the iteration
        virtual T next() = 0;
        // Removes last element listed from the collection
        virtual void remove() = 0;
};

#endif	/* ITERATOR_H */

