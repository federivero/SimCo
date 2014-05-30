
#include "../processor/RegisterFile.h"
#include "MIPS32ISA.h"
#include "../exceptions/IllegalInstructionLengthException.h"
#include "../exceptions/IllegalInstructionBinaryException.h"
#include "../exceptions/IllegalInstructionSyntaxException.h"
#include "Operand.h"
#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

MIPS32ISA* MIPS32ISA::instance = NULL;

MIPS32ISA::MIPS32ISA(){
    nop_  = new StaticInstruction(0,INSTRUCTION_TYPE_NOP);
    
    add_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    and_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    or_   = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    sub_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    sll_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    srl_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    xor_  = new StaticInstruction(3,INSTRUCTION_TYPE_INT_ALU);
    
    ll_   = new StaticInstruction(2,INSTRUCTION_TYPE_READ_MODIFY_WRITE);
    sc_   = new StaticInstruction(2,INSTRUCTION_TYPE_READ_MODIFY_WRITE);
    
    jal_  = new StaticInstruction(1,INSTRUCTION_TYPE_JUMP_BRANCH);
    jalr_ = new StaticInstruction(2,INSTRUCTION_TYPE_JUMP_BRANCH);
    bne_  = new StaticInstruction(2,INSTRUCTION_TYPE_JUMP_BRANCH);
    bnez_ = new StaticInstruction(2,INSTRUCTION_TYPE_JUMP_BRANCH);
    
    lw_   = new StaticInstruction(2,INSTRUCTION_TYPE_LOAD_STORE);
    sw_   = new StaticInstruction(2,INSTRUCTION_TYPE_LOAD_STORE);
    
    syscall_ = new StaticInstruction(0,INSTRUCTION_TYPE_SYSCALL);
}

MIPS32ISA* MIPS32ISA::getInstance(){
    if (MIPS32ISA::instance == NULL){
        MIPS32ISA::instance = new MIPS32ISA();
    }
    return MIPS32ISA::instance;
}

unsigned int decodeRegisterOperand(char* operand){
    string s = operand;
    unsigned int result = 0;
    if (operand[0] == 'R'){
        result = atoi(s.substr(1,s.size()).c_str());
    }else{
        throw new IllegalInstructionSyntaxException("Illegal operand for instruction");
    }
    return result;
}

unsigned int decodeIntOperand(char* operand){
    string s = operand;
    unsigned int result = 0;
    result = atoi(s.substr(1,s.size()).c_str());
    return result;
}

unsigned int decodeLabelOperand(char* operand){
    return 0;
}

Instruction* MIPS32ISA::buildInstruction(char* opcode, char** operands, int operandsLength){
    /* TODO: use TRIE tree to do this faster? */
    /* TODO: Pooling? */
    StaticInstruction* archetype = NULL;
    InstructionEncodingType encodingType;
    MIPS32_InstructionEncodingSubtype encodingSubtype;
    unsigned char binOpcode = 0;
    unsigned short sourceRegisterOne = 0;
    unsigned short sourceRegisterTwo = 0;
    unsigned short destinationRegister = 0;
    unsigned int shiftAmmount = 0;
    unsigned int immediate = 0;
    unsigned char function = 0;
    MemoryChunk* rawInstruction;
    unsigned char* bytes;
    if (strcmp(opcode,"ADD") == 0){
        archetype = add_;
        encodingSubtype = MIPS32_ARITHLOG;
        function = 32; /* 100000 */
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"AND") == 0){ 
        encodingSubtype = MIPS32_ARITHLOG;
        archetype = and_;
        function = 36;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"XOR") == 0){
        encodingSubtype = MIPS32_ARITHLOG;
        archetype = xor_; 
        function = 38; /* 100110 */
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"BNE") == 0){
        archetype = bne_;
        encodingSubtype = MIPS32_BRANCH;
        binOpcode = OP_BNE;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"JAL") == 0){
        archetype = jal_;
        encodingSubtype = MIPS32_JUMP;
        binOpcode = OP_JAL;
        encodingType = MIPS32_J_FORMAT;
    }else if (strcmp(opcode,"JALR") == 0){
        archetype = jalr_;
        encodingSubtype = MIPS32_JUMPR;
        binOpcode = OP_JALR;
        encodingType = MIPS32_J_FORMAT;
    }else if (strcmp(opcode,"LW") == 0){
        archetype = lw_;
        encodingSubtype = MIPS32_LOADSTORE;
        binOpcode = OP_LW;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"SLL") == 0){
        archetype = sll_;
        encodingSubtype = MIPS32_SHIFT;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"SRL") == 0){
        archetype = srl_;
        function = 2;
        encodingSubtype = MIPS32_SHIFT;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"SUB") == 0){
        archetype = sub_;
        function = 34;
        encodingSubtype = MIPS32_ARITHLOG;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"SW") == 0){
        archetype = sw_;
        binOpcode = OP_SW;
        encodingSubtype = MIPS32_LOADSTORE;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"SYSCALL") == 0){
        // Fake instruction to end execution
        bytes = new unsigned char[4];
        bytes[0] = 255;
        bytes[1] = 255;
        bytes[2] = 255;
        bytes[3] = 255;
        rawInstruction = new MemoryChunk(bytes,4);
    }else{
        throw new IllegalInstructionSyntaxException("Illegal opcode");
    }
    if (encodingType == MIPS32_R_FORMAT){
        if (encodingSubtype == MIPS32_ARITHLOG){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterOne = decodeRegisterOperand(operands[1]);
            sourceRegisterTwo = decodeRegisterOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_DIVMULT){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
        }else if (encodingSubtype == MIPS32_SHIFT){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            shiftAmmount = decodeIntOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_SHIFTV){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            sourceRegisterOne = decodeRegisterOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_JUMPR || encodingSubtype == MIPS32_MOVETO){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
        }else if (encodingSubtype == MIPS32_MOVEFROM){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
        }
        bytes = new unsigned char[4];
        bytes[0] = ((binOpcode & 0x003F) << 2) | ((sourceRegisterOne & 0x0018) >> 3);
        bytes[1] = ((sourceRegisterOne & 0x0007) << 5) | (sourceRegisterTwo & 0x001F);
        bytes[2] = ((destinationRegister & 0x001F) << 3) | (shiftAmmount & 0x001C << 2);
        bytes[3] = ((shiftAmmount & 0x0003) << 6) | (function & 0x003F);
        rawInstruction = new MemoryChunk(bytes,4);
    }else if (encodingType == MIPS32_I_FORMAT){
        if (encodingSubtype == MIPS32_ARITHLOGI){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            sourceRegisterOne = decodeRegisterOperand(operands[1]);
            immediate = decodeIntOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_LOADI){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            immediate = decodeIntOperand(operands[1]);
        }else if (encodingSubtype == MIPS32_BRANCH){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            immediate = decodeLabelOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_BRANCHZ){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            immediate = decodeLabelOperand(operands[1]);
        }else if (encodingSubtype == MIPS32_LOADSTORE){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            immediate = decodeLabelOperand(operands[1]);
            sourceRegisterOne = decodeRegisterOperand(operands[2]);
        }
        // TODO: build RAW instruction!
    }else if (encodingType == MIPS32_J_FORMAT){
        if (encodingSubtype == MIPS32_JUMP){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            immediate = decodeLabelOperand(operands[0]);
        }else if (encodingSubtype == MIPS32_TRAP){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for instruction");
            }
            immediate = decodeIntOperand(operands[0]);
        }
        // TODO: build RAW instruction!    
    }
    /* Check for valid values */
    if ((sourceRegisterOne >= MIPS32REGISTERCOUNT) || 
            (sourceRegisterTwo >= MIPS32REGISTERCOUNT) || 
            (destinationRegister >= MIPS32REGISTERCOUNT)){
        throw new IllegalInstructionSyntaxException("Register number is too big");
    }else if( (immediate >= (1 << 16) && encodingType == MIPS32_I_FORMAT) ||
               (immediate >= (1 << 26) && encodingType == MIPS32_J_FORMAT)){
        throw new IllegalInstructionSyntaxException("Immediate is too big");
    }else if (shiftAmmount >= (1 << 5)){
        throw new IllegalInstructionSyntaxException("Shift ammount is too big");
    }
    Instruction* retVal = new Instruction();
    retVal->setArchetype(archetype);
    retVal->setInstructionOpcode(binOpcode);
    retVal->setRawInstruction(rawInstruction);
    return retVal;
}

Instruction* MIPS32ISA::decodeInstruction(MemoryChunk* rawInst){
    if (rawInst->getBytesLength() != 4){
        throw new IllegalInstructionLengthException("MIPS32ISA instructions are 4 bytes long");
    }else{
        unsigned char* bytes = rawInst->getBytes();
        Instruction* inst;
        Operand* sourceOperandOne;
        Operand* sourceOperandTwo;
        Operand* destinationOperand;
        ALUFunction aluFunction;
        unsigned char opcode = (0xFC & bytes[0]) >> 2;
        unsigned int sourceRegisterOne;
        unsigned int sourceRegisterTwo;
        unsigned int destinationRegister;
        unsigned int shiftAmmount;
        unsigned int immediate;
        unsigned char function;
        StaticInstruction* archetype = NULL;
        switch(opcode){
            case 0:
                /* Opcode 0 resumes all R type instruction, decode operands
                 * Register Format:  ooooooss sssttttt dddddaaa aaffffff */
                sourceRegisterOne = ((0x3 & bytes[0]) << 3) | ((0xE0 & bytes[1]) >> 5);
                sourceRegisterTwo = 0x1F & bytes[1];
                destinationRegister = (0xF8 & bytes[2]) >> 3;
                shiftAmmount = (0x07 & bytes[2] << 3) | ((0xC0 & bytes[3]) >> 6);
                function = 0x3F & bytes[3];
                /* Check if function binary is legal*/
                switch (function){
                    case 0:  /* sll */
                    case 2:  /* srl */
                    case 3:  /* sra */
                    case 4:  /* sllv */
                    case 6:  /* srlv */
                    case 7:  /* srav */
                    case 16: /* mfhi */
                    case 17: /* mthi */
                    case 18: /* mflo */
                    case 19: /* mtlo */
                        aluFunction = ALU_FUNCTION_MOV; break;
                    case 24: /* mult */
                    case 25: /* multu */
                    case 26: /* div */
                    case 27: /* divu */
                    case 32: /* add */
                        aluFunction = ALU_FUNCTION_INT_ADD; break; 
                    case 33: /* addu */
                    case 34: /* sub */ 
                    case 35: /* subu */
                    case 36: /* and */
                    case 37: /* or */
                    case 38: /* xor */
                        aluFunction = ALU_FUNCTION_XOR; break;
                    case 39: /* nor */
                    case 41: /* sltu */
                    case 42: /* slt */
                        break;
                    default:
                        //string msg = "Illegal instruction binary";
                        //msg.append(())
                        throw new IllegalInstructionBinaryException("Illegal MIPS32 instruction ALU function");
                }
                sourceOperandOne = new RegisterOperand();
                sourceOperandTwo = new RegisterOperand();
                destinationOperand = new RegisterOperand();
                inst = new ALUInstruction(3,aluFunction);
                ((RegisterOperand*) sourceOperandOne)->setRegisterNumber(sourceRegisterOne);
                ((RegisterOperand*) sourceOperandTwo)->setRegisterNumber(sourceRegisterTwo);
                ((RegisterOperand*) destinationOperand)->setRegisterNumber(destinationRegister);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(sourceOperandTwo,1);
                inst->setOperand(destinationOperand,2);
                break;
            case 2:  /* j */
            case 3:  /* jal */
            case 26: /* trap */
                /* Jump Instruction format: ooooooii iiiiiiii iiiiiiii iiiiiiii*/ 
                immediate = 
                        (((bytes[0] & 0x03) << 24) | 
                          (bytes[1] << 16) | 
                          (bytes[2] << 8) | 
                          (bytes[3]));
                //inst->setImmediate(immediate);
                break;
            case 4:  /* beq */
            case 5:  /* bne */
            case 6:  /* blez */
            case 7:  /* bgtz */
            case 8:  /* addi */
            case 9:  /* addiu */
            case 10: /* slti */
            case 11: /* sltiu */
            case 12: /* andi */
            case 13: /* ori */
            case 14: /* xori */
            case 24: /* llo */
            case 25: /* lhi */
            case 32: /* lb */
            case 33: /* lh */
            case 35: /* lw */
            case 36: /* lbu */
            case 37: /* lhu */
            case 40: /* sb */
            case 41: /* sh */
            case 43: /* sw */
                /* Immediate format: ooooooss sssttttt iiiiiiii iiiiiiii*/
                sourceRegisterOne = ((0x3 & bytes[0]) << 3) | ((0xE0 & bytes[1]) >> 5);
                sourceRegisterTwo = 0x1F & bytes[1];
                //inst->setSourceRegisterOne(sourceRegisterOne);
                //inst->setSourceRegisterTwo(sourceRegisterTwo);
                immediate = ((bytes[2]) << 8) | bytes[3];
                //inst->setImmediate(immediate);
                break;
            case 63:
                // System Call 
                inst = new Instruction();
                break;
            default:
                throw new IllegalInstructionBinaryException("Illegal MIPS32 instruction opcode");
                break;
        }
        // Pass again and set Archetype
        switch(opcode){
            case 0:
                switch (function){
                    case 0:  /* sll */
                    case 2:  /* srl */
                    case 3:  /* sra */
                    case 4:  /* sllv */
                    case 6:  /* srlv */
                    case 7:  /* srav */
                    case 16: /* mfhi */
                    case 17: /* mthi */
                    case 18: /* mflo */
                    case 19: /* mtlo */
                        aluFunction = ALU_FUNCTION_MOV; break;
                    case 24: /* mult */
                    case 25: /* multu */
                    case 26: /* div */
                    case 27: /* divu */
                    case 32: /* add */
                        aluFunction = ALU_FUNCTION_INT_ADD; break; 
                    case 33: /* addu */
                    case 34: /* sub */ 
                    case 35: /* subu */
                    case 36: /* and */
                    case 37: /* or */
                    case 38: /* xor */
                        archetype = xor_;
                        break;
                    case 39: /* nor */
                    case 41: /* sltu */
                    case 42: /* slt */
                        break;
                }
                break;
            case 63:
                archetype = syscall_;
                break;
            // TODO! Complete rest of instructions
            default:
                break;
        }
        
        // Last, add general information and return
        inst->setRawInstruction(rawInst);
        inst->setArchetype(archetype);
        return inst;
    }
}

/* Given an instruction, returns the binary encoding of that instruction */
MemoryChunk* MIPS32ISA::encodeInstruction(Instruction* inst){
    return inst->getRawInstruction();
    /*
    // TODO: Pooling? 
    bytesLength = 4;
    bytes = new unsigned char[bytesLength];
    StaticInstruction* arch = inst->getArchetype();
    unsigned short opcode;
    unsigned short function;
    unsigned short sourceRegisterOne;
    unsigned short sourceRegisterTwo;
    unsigned short destinationRegister;
    InstructionEncodingType instructionEncodingType;
    unsigned short shiftAmmount;
    unsigned int immediate;
        
    
    if (instructionEncodingType == MIPS32_R_FORMAT){
        bytes[0] = ((opcode & 0x003F) << 2) | ((sourceRegisterOne & 0x0018) >> 3);
        bytes[1] = ((sourceRegisterOne & 0x0007) << 5) | (sourceRegisterTwo & 0x001F);
        bytes[2] = ((destinationRegister & 0x001F) << 3) | (shiftAmmount & 0x001C << 2);
        bytes[3] = ((shiftAmmount & 0x0003) << 6) | (function & 0x003F);
    }else if (instructionEncodingType == MIPS32_I_FORMAT){
        bytes[0] = ((opcode & 0x003F) << 2) | ((sourceRegisterOne & 0x0018) >> 3);
        bytes[1] = ((sourceRegisterOne & 0x0007) << 5) | (sourceRegisterTwo & 0x001F);
        bytes[2] = (immediate & 0x0000FF00) >> 8;
        bytes[3] = immediate & 0xFF;
    }else if (instructionEncodingType == MIPS32_J_FORMAT){
        bytes[0] = ((opcode & 0x003F) << 2) | ((immediate & 0x03000000) >> 3);
        bytes[1] = (immediate & 0x00FF0000) >> 16;
        bytes[2] = (immediate & 0x0000FF00) >> 8;
        bytes[3] =  immediate & 0x000000FF;
    } // No other options, its coded like this for simplicity while reading
    */
}

RegisterFile* MIPS32ISA::createArchitectedRegisterFile(){
    return new RegisterFile(MIPS_32_INTEGER_REGISTER_COUNT,MIPS_32_FLOATING_POINT_REGISTER_COUNT);
}

int MIPS32ISA::getInstructionLength(){
    return MIPS_32_INSTRUCTION_LENGTH;
}

