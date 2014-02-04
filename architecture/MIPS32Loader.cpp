
#include "MIPS32Loader.h"
#include "../common/SimpleFileParser.h"
#include "../exceptions/IllegalInstructionSyntaxException.h"
#include "../exceptions/RuntimeException.h"
#include "MIPS32ISA.h"
#include <string>
#include <string.h>

using namespace std;

MIPS32Loader::MIPS32Loader(MemorySystem* memSystem):Loader(memSystem,MIPS32ISA::getInstance()){
    
}

void MIPS32Loader::loadProgram(char* fileName, MemoryAddress * initialAddress){
    SimpleFileParser sfp;
    if (!sfp.open(fileName)){
        throw new RuntimeException("Unable to open program file");
    }
    sfp.set_single_char_tokens(";,");
    char** instructionOperands = new char*[256];
    // Read the lines and generate an instruction for each one
    while(sfp.get_next_line()){
        int validOperandCount = 0;
        if (sfp.get_num_tokens() > 0){
            string instructionName;
            instructionName = sfp.get_token(0);
            for (int i = 0; i < sfp.get_num_tokens(); i++){
                instructionOperands[validOperandCount] = (char*) sfp.get_token(i).c_str();
                if (strcmp(instructionOperands[i],";")==0){
                    break;
                }else if (strcmp(instructionOperands[i],",")){
                    continue;
                }else{
                    validOperandCount++;
                }
            }
            Instruction* inst = instructionSetArchitecture->buildInstruction((char*)instructionName.c_str(),instructionOperands,validOperandCount);
            memorySystem->setMemoryContent(inst->getRawInstruction(),initialAddress);
        }else{
            string message = "String invalid for instruction. Line: ";
            char* lNumber = new char[256];
            message.append(itoa(sfp.get_line_number(),lNumber,10));
            throw new IllegalInstructionSyntaxException(message.c_str());
        }
    }
}



