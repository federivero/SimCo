/* 
 * File:   IllegalInstructionSyntaxException.h
 * Author: fede
 *
 * Created on 28 de enero de 2014, 06:00 PM
 */

#ifndef ILLEGALINSTRUCTIONSYNTAXEXCEPTION_H
#define	ILLEGALINSTRUCTIONSYNTAXEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class IllegalInstructionSyntaxException : public exception{
        private:
            string err_msg;
        public:
            IllegalInstructionSyntaxException(const char* msg) : err_msg(msg){};
            ~IllegalInstructionSyntaxException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};

#endif	/* ILLEGALINSTRUCTIONSYNTAXEXCEPTION_H */

