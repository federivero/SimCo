/* 
 * File:   IllegalInstructionLengthException.h
 * Author: fede
 *
 * Created on 24 de enero de 2014, 04:15 PM
 */

#ifndef ILLEGALINSTRUCTIONLENGTHEXCEPTION_H
#define	ILLEGALINSTRUCTIONLENGTHEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class IllegalInstructionLengthException : public exception{
        private:
            string err_msg;
        public:
            IllegalInstructionLengthException(const char* msg) : err_msg(msg){};
            ~IllegalInstructionLengthException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};

#endif	/* ILLEGALINSTRUCTIONLENGTHEXCEPTION_H */

