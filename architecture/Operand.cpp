
#include "../processor/Register.h"
#include "Operand.h"
#include <stdio.h>

/* Operand */
Operand::Operand(OperandType opType){
    this->type = opType;
}

OperandType Operand::getType(){
    return type;
}

unsigned long Operand::getOperandBinaryValue(){
    return operandValue;
}

void Operand::setOperandBinaryValue(unsigned long binaryOperandValue){
    operandValue = binaryOperandValue;
}

/* SpecialRegisterType operations */
SpecialRegisterOperand::SpecialRegisterOperand(SpecialRegisterType regType):Operand(OPERAND_TYPE_SPECIAL_REGISTER){
    this->type = regType;
}

SpecialRegisterType SpecialRegisterOperand::getSpecialRegisterType(){
    return type;
}

/* Register Operand operations */
RegisterOperand::RegisterOperand(int registerNumber, RegisterType type):Operand(OPERAND_TYPE_REGISTER){
    this->registerNumber = registerNumber;
    this->registerType = type;
}

RegisterType RegisterOperand::getRegisterType(){
    return registerType;
}

void RegisterOperand::setRegisterType(RegisterType type){
    this->registerType = type;
}
        
int RegisterOperand::getRegisterNumber(){
    return registerNumber;
}

void RegisterOperand::setRegisterNumber(int regNumber){
    registerNumber = regNumber;
}

/* Immediate Operand operatinos */
ImmediateOperand::ImmediateOperand(long value):Operand(OPERAND_TYPE_IMMEDIATE){
    setOperandBinaryValue(value);
}


// Indexed Operand operations

IndexedOperand::IndexedOperand(long immediateValue, int registerNumber):Operand(OPERAND_TYPE_INDEXED){
    this->immediate = immediateValue;
    this->registerNumber = registerNumber;
}

int IndexedOperand::getRegisterNumber(){
    return registerNumber;
}

 long IndexedOperand::getImmediateValue(){
     return immediate;
 }
    


