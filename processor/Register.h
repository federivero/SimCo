/* 
 * File:   Register.h
 * Author: fede
 *
 * Created on 22 de enero de 2014, 02:07 PM
 */

#ifndef REGISTER_H
#define	REGISTER_H

#include <iostream>
#include <fstream>

enum RegisterType{
    REGISTER_TYPE_INT, REGISTER_TYPE_FP, REGISTER_TYPE_PC
};

enum SpecialRegisterType{
    SPECIAL_REGISTER_PC
};

using namespace std;

class InstructionResult;

class Register{
    private:
        RegisterType registerType;
        int registerNumber;
    public:
        Register(RegisterType type, int registerNumber);
        RegisterType getRegisterType();
        int getRegisterNumber();
        
        /* Polymorphic operation to set register result */
        virtual void setRegisterValue(InstructionResult* result) = 0;
        virtual void printRegisterValue(ofstream* file) = 0;
};

class FPRegister: public Register{
    private:
        float value;
        
    public:
        FPRegister(int registerNumber);
        float getRegisterValue();
        void setRegisterValue(float newValue);
        
        void setRegisterValue(InstructionResult* result);
        void printRegisterValue(ofstream* file);
};

class IntRegister: public Register{
    private:
        int value;
        
    public:
        IntRegister(int registerNumber);
        int getRegisterValue();
        void setRegisterValue(int newValue);
        
        void setRegisterValue(InstructionResult* result);
        void printRegisterValue(ofstream* file);
};

#endif	/* REGISTER_H */

