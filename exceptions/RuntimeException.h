/* 
 * File:   RuntimeException.h
 * Author: fede
 *
 * Created on 20 de enero de 2014, 12:34 PM
 */

#ifndef RUNTIMEEXCEPTION_H
#define	RUNTIMEEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class RuntimeException : public exception{
        private:
            string err_msg;
        public:
            RuntimeException(const char* msg) : err_msg(msg){};
            ~RuntimeException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};

#endif	/* RUNTIMEEXCEPTION_H */

