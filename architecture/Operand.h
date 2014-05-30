/* 
 * File:   Operand.h
 * Author: fede
 *
 * Created on 13 de mayo de 2014, 04:34 PM
 */

#ifndef OPERAND_H
#define	OPERAND_H

enum OperandType{
    OPERAND_TYPE_IMMEDIATE, OPERAND_TYPE_REGISTER
};

#include "../processor/Register.h"

class Operand{
    private:
        OperandType type;
    
    public:
        Operand(OperandType opType);
        OperandType getType();
};

class RegisterOperand: public Operand{
    
    private:
        Register* reg;
        int registerNumber;
        RegisterType registerType;
    public:
        RegisterOperand();
        Register* getRegister();
        void setRegister(Register* reg);
        RegisterType getType();
        void setRegisterType(RegisterType type);
        int getRegisterNumber();
        void setRegisterNumber(int registerNumber);
};   

class ImmediateOperand: public Operand{

    private:

        long operandValue;

    public:
    
        ImmediateOperand(long operandValue);
};


#endif	/* OPERAND_H */

