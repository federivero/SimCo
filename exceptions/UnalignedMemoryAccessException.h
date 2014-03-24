/* 
 * File:   UnalignedMemoryAccessException.h
 * Author: fede
 *
 * Created on 4 de marzo de 2014, 05:34 PM
 */

#ifndef UNALIGNEDMEMORYACCESSEXCEPTION_H
#define	UNALIGNEDMEMORYACCESSEXCEPTION_H

class UnalignedMemoryAccessException : public exception{
        private:
            string err_msg;
        public:
            UnalignedMemoryAccessException(const char* msg) : err_msg(msg){};
            ~UnalignedMemoryAccessException() throw() {};
            const char* what() const throw() { return this->err_msg.c_str(); };
};

#endif	/* UNALIGNEDMEMORYACCESSEXCEPTION_H */

