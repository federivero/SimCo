/* 
 * File:   Operand.h
 * Author: fede
 *
 * Created on 13 de mayo de 2014, 04:34 PM
 */

#ifndef OPERAND_H
#define	OPERAND_H

enum OperandType{
    OPERAND_TYPE_IMMEDIATE, OPERAND_TYPE_REGISTER, OPERAND_TYPE_SPECIAL_REGISTER, OPERAND_TYPE_INDEXED
};

#include "../processor/Register.h"

class Operand{
    private:
        OperandType type;
        unsigned long operandValue;
    public:
        Operand(OperandType opType);
        OperandType getType();
        unsigned long getOperandBinaryValue();
        void setOperandBinaryValue(unsigned long binaryOperandValue);
};

class SpecialRegisterOperand: public Operand{
    private:
        SpecialRegisterType type;
    public:
        SpecialRegisterOperand(SpecialRegisterType regType);
        SpecialRegisterType getSpecialRegisterType();
};

class RegisterOperand: public Operand{
    
    private:
        int registerNumber;
        RegisterType registerType;
    public:
        RegisterOperand(int registerNumber, RegisterType regType);
        RegisterType getRegisterType();
        void setRegisterType(RegisterType type);
        int getRegisterNumber();
        void setRegisterNumber(int registerNumber);
};   

class ImmediateOperand: public Operand{

    private:
        
    public:
        ImmediateOperand(long operandValue);
};

class IndexedOperand: public Operand{
    private:
        int registerNumber; // Only int registers allowed
        long immediate;
    public:
        IndexedOperand(long immediateValue, int registerNumber);
        int getRegisterNumber();
        long getImmediateValue();
};

#endif	/* OPERAND_H */

