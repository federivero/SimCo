/* 
 * File:   IllegalInstructionBinaryException.h
 * Author: fede
 *
 * Created on 24 de enero de 2014, 05:58 PM
 */

#ifndef ILLEGALINSTRUCTIONBINARYEXCEPTION_H
#define	ILLEGALINSTRUCTIONBINARYEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class IllegalInstructionBinaryException : public exception{
        private:
            string err_msg;
        public:
            IllegalInstructionBinaryException(const char* msg) : err_msg(msg){};
            ~IllegalInstructionBinaryException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};

#endif	/* ILLEGALINSTRUCTIONBINARYEXCEPTION_H */

