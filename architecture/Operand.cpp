
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

/* Register Operand operations */
RegisterOperand::RegisterOperand():Operand(OPERAND_TYPE_REGISTER){
    reg = NULL;
}

Register* RegisterOperand::getRegister(){
    return reg;
}

void RegisterOperand::setRegister(Register* reg){
    this->reg = reg;
}

RegisterType RegisterOperand::getType(){
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
    this->operandValue = value;
}



    


