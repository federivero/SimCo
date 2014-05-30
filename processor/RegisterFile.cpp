
#include "RegisterFile.h"
#include <stdio.h>


RegisterFile::RegisterFile(int integerRegisterCount, int floatingPointRegisterCount){
    this->intRegisterCount = integerRegisterCount;
    this->floatingPointRegisterCount = floatingPointRegisterCount;
    if (integerRegisterCount > 0){
        this->integerRegisterFile = new IntRegister*[integerRegisterCount];
        for (int i = 0; i < integerRegisterCount; i++){
            integerRegisterFile[i] = new IntRegister(i);
        }
    }else{
        integerRegisterFile = NULL;
    }
    if (floatingPointRegisterCount > 0){
        this->floatingPointRegisterFile = new FPRegister*[floatingPointRegisterCount];
        for (int i = 0; i < floatingPointRegisterCount; i++){
            this->floatingPointRegisterFile[i] = new FPRegister(i);
        }
    }else{
        floatingPointRegisterFile = NULL;
    }
}

/* Register File Handling methods*/
FPRegister* RegisterFile::getFloatingPointRegister(int registerNumber){
    return floatingPointRegisterFile[registerNumber];
}

float RegisterFile::getFloatingPointRegisterValue(int registerNumber){
    return floatingPointRegisterFile[registerNumber]->getRegisterValue();
}

void RegisterFile::setFloatingPointRegisterValue(int registerNumber, float value){
    floatingPointRegisterFile[registerNumber]->setRegisterValue(value);
}

IntRegister* RegisterFile::getIntegerRegister(int registerNumber){
    return integerRegisterFile[registerNumber];
}

int RegisterFile::getIntegerRegisterValue(int registerNumber){
    return integerRegisterFile[registerNumber]->getRegisterValue();
}

void RegisterFile::setIntegerRegisterValue(int registerNumber, int value){
    integerRegisterFile[registerNumber]->setRegisterValue(value);
}


