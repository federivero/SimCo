
#include "Register.h"
#include "../architecture/Instruction.h"
#include "../exceptions/RuntimeException.h"

Register::Register(RegisterType type, int registerNumber):registerType(type){
    this->registerNumber = registerNumber;
}

RegisterType Register::getRegisterType(){
    return registerType;
}

int Register::getRegisterNumber(){
    return registerNumber;
}

/* FPRegister operations */
FPRegister::FPRegister(int registerNumber):Register(REGISTER_TYPE_FP,registerNumber){
    value = 0;
}

float FPRegister::getRegisterValue(){
    return value;
}

void FPRegister::setRegisterValue(float newValue){
    value = newValue;
}

void FPRegister::setRegisterValue(InstructionResult* result){
    if (result->getType() != INSTRUCTION_RESULT_FP){
        throw new RuntimeException((char*)"Assigning a non-FP value to an FP register");
    }
    InstructionResultFP* instResult = (InstructionResultFP*) result;
    this->value = instResult->getResult();
}

void FPRegister::printRegisterValue(ofstream* file){
    *file << value;
}

/* IntRegister operations */
IntRegister::IntRegister(int registerNumber):Register(REGISTER_TYPE_INT,registerNumber){
    this->value = 0;
}

int IntRegister::getRegisterValue(){
    return value;
}

void IntRegister::setRegisterValue(int newValue){
    value = newValue;
}

void IntRegister::setRegisterValue(InstructionResult* result){
    if (result->getType() != INSTRUCTION_RESULT_INT){
        throw new RuntimeException("Assigning a non-int value to an int register");
    }
    InstructionResultInt* instResult = (InstructionResultInt*) result;
    this->value = instResult->getResult();
}

void IntRegister::printRegisterValue(ofstream* file){
    *file << value;
}
