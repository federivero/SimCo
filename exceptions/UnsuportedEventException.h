/* 
 * File:   UnsuportedEventException.h
 * Author: fede
 *
 * Created on 17 de marzo de 2014, 11:05 PM
 */

#ifndef UNSUPORTEDEVENTEXCEPTION_H
#define	UNSUPORTEDEVENTEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class UnsuportedEventException : public exception{
        private:
            string err_msg;
        public:
            UnsuportedEventException(const char* msg) : err_msg(msg){};
            ~UnsuportedEventException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};


#endif	/* UNSUPORTEDEVENTEXCEPTION_H */

