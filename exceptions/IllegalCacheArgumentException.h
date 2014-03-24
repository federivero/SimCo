/* 
 * File:   IllegalCacheArgumentException.h
 * Author: fede
 *
 * Created on 4 de marzo de 2014, 05:08 PM
 */

#ifndef ILLEGALCACHEARGUMENTEXCEPTION_H
#define	ILLEGALCACHEARGUMENTEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class IllegalCacheArgumentException : public exception{
        private:
            string err_msg;
        public:
            IllegalCacheArgumentException(const char* msg) : err_msg(msg){};
            ~IllegalCacheArgumentException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};


#endif	/* ILLEGALCACHEARGUMENTEXCEPTION_H */

