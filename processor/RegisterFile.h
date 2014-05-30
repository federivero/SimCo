/* 
 * File:   RegisterBank.h
 * Author: fede
 *
 * Created on 12 de mayo de 2014, 05:04 PM
 */

#ifndef REGISTERFILE_H
#define	REGISTERFILE_H

#include "Register.h"

/* This class encapsulates the functionality of the register file.*/
class RegisterFile{
    
    private:
        int intRegisterCount;
        IntRegister** integerRegisterFile;
        
        int floatingPointRegisterCount;
        FPRegister** floatingPointRegisterFile;
        
    public:
        /* Construction Methods */
        RegisterFile(int integerRegisterCount, int foatingPointRegisterCount);
        
        /* Accesing Methods */
        FPRegister* getFloatingPointRegister(int registerNumber);
        IntRegister* getIntegerRegister(int registerNumber);
        float getFloatingPointRegisterValue(int registerNumber);
        void setFloatingPointRegisterValue(int registerNumber, float value);
        int getIntegerRegisterValue(int registerNumber);
        void setIntegerRegisterValue(int registerNumber, int value);
        
    
};

#endif	/* REGISTERBANK_H */

