
#include "../common/Map.h"
#include "MIPS32Loader.h"
#include "../common/SimpleFileParser.h"
#include "../exceptions/IllegalInstructionSyntaxException.h"
#include "../exceptions/RuntimeException.h"
#include "MIPS32ISA.h"
#include <string>
#include <string.h>

#define ORG_COMMAND "ORG"

using namespace std;

MIPS32Loader::MIPS32Loader(MemorySystem* memSystem):Loader(memSystem,MIPS32ISA::getInstance()){
    
}

void MIPS32Loader::loadProgram(char* fileName){
    SimpleFileParser sfp;
    if (!sfp.open(fileName)){
        throw new RuntimeException("Unable to open program file");
    }
    sfp.set_single_char_tokens(";,:");
    char** instructionOperands = new char*[256];
    unsigned long address = 0; // Default start address 
    // Read the lines and generate an instruction for each one
    while(sfp.get_next_line()){
        int validOperandCount = 0;
        string firstToken;
        if (sfp.get_num_tokens() > 0){
            firstToken = sfp.get_token(0);
            if (firstToken[0] != '#'){
                if ((sfp.get_num_tokens() > 1) && sfp.get_token(1)[0] == ':'){ // Tag definition line
                    tagMap->put(firstToken,address);
                }else if (firstToken.compare(ORG_COMMAND) == 0){
                    string strAddress = sfp.get_token(1);
                    int base = 16;
                    // If address starts with 0x then its an hexadecimal number
                    if (strAddress.find("0x") != 0){
                        base = 10;
                    }
                    address = strtol(strAddress.c_str(),NULL,base);
                }else{
                    for (int i = 1; i < sfp.get_num_tokens() ; i++){
                        instructionOperands[validOperandCount] = (char*) sfp.get_token(i).c_str();
                        if (strcmp(instructionOperands[validOperandCount],";")==0){
                            break;
                        }else if (strcmp(instructionOperands[validOperandCount],",")==0){
                            continue;
                        }else{
                            validOperandCount++;
                        }
                    }
                    MemoryChunk* inst = instructionSetArchitecture->buildInstruction((char*)firstToken.c_str(),instructionOperands,validOperandCount);
                    memorySystem->setMemoryContent(inst,address);
                    address = address + inst->getBytesLength();
                }
            }
        }
    }
}



