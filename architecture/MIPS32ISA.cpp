
#include "../processor/RegisterFile.h"
#include "MIPS32ISA.h"
#include "../exceptions/IllegalInstructionLengthException.h"
#include "../exceptions/IllegalInstructionBinaryException.h"
#include "../exceptions/IllegalInstructionSyntaxException.h"
#include "Operand.h"
#include "MIPS32Loader.h"
#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

MIPS32ISA* MIPS32ISA::instance = NULL;

MIPS32ISA::MIPS32ISA(){
    nop_  = new StaticInstruction(0,0,INSTRUCTION_TYPE_NOP);
    
    add_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    and_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    or_   = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    sub_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    sll_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    sllv_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    sra_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    srav_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    srl_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    srlv_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    xor_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    xori_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    ori_  = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    andi_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    addi_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    addiu_ = new StaticInstruction(2,1,INSTRUCTION_TYPE_INT_ALU);
    
    ll_   = new StaticInstruction(1,1,INSTRUCTION_TYPE_READ_MODIFY_WRITE);
    sc_   = new StaticInstruction(2,1,INSTRUCTION_TYPE_READ_MODIFY_WRITE);
    
    llo_ = new StaticInstruction(2,1, INSTRUCTION_TYPE_INT_ALU);
    lhi_ = new StaticInstruction(2,1, INSTRUCTION_TYPE_INT_ALU);
    
    jal_  = new StaticInstruction(1,1, INSTRUCTION_TYPE_JUMP);
    jalr_ = new StaticInstruction(2,1, INSTRUCTION_TYPE_JUMP);
    bne_  = new StaticInstruction(4,1,INSTRUCTION_TYPE_BRANCH);
    beq_ =  new StaticInstruction(4,1,INSTRUCTION_TYPE_BRANCH);
    bgtz_ = new StaticInstruction(4,1,INSTRUCTION_TYPE_BRANCH);
    blez_ = new StaticInstruction(4,1,INSTRUCTION_TYPE_BRANCH);
    
    lb_   = new StaticInstruction(1,1,INSTRUCTION_TYPE_LOAD_STORE);
    lbu_  = new StaticInstruction(1,1,INSTRUCTION_TYPE_LOAD_STORE);
    lh_   = new StaticInstruction(1,1,INSTRUCTION_TYPE_LOAD_STORE);
    lhu_  = new StaticInstruction(1,1,INSTRUCTION_TYPE_LOAD_STORE);
    sb_   = new StaticInstruction(2,1,INSTRUCTION_TYPE_LOAD_STORE);
    sh_   = new StaticInstruction(2,1,INSTRUCTION_TYPE_LOAD_STORE);
    lw_   = new StaticInstruction(1,1,INSTRUCTION_TYPE_LOAD_STORE);
    sw_   = new StaticInstruction(2,1,INSTRUCTION_TYPE_LOAD_STORE);
    
    syscall_ = new StaticInstruction(0,0,INSTRUCTION_TYPE_SYSCALL);
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
    result = atoi(s.c_str());
    return result;
}

unsigned long decodeLabelOperand(char* operand, Loader* loader){
    return loader->getTagValue(operand);
}

MemoryChunk* MIPS32ISA::buildInstruction(char* opcode, char** operands, int operandsLength){
    /* TODO: use TRIE tree to do this faster? */
    /* TODO: Pooling? */
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
        encodingSubtype = MIPS32_ARITHLOG;
        function = MIPS32FUNCTION_ADD; /* 100000 */
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"AND") == 0){ 
        encodingSubtype = MIPS32_ARITHLOG;
        function = MIPS32FUNCTION_AND;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"XOR") == 0){
        encodingSubtype = MIPS32_ARITHLOG;
        function = MIPS32FUNCTION_XOR; /* 100110 */
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"OR") == 0){
        encodingSubtype = MIPS32_ARITHLOG;
        function = MIPS32FUNCTION_OR; /* 100110 */
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"BNE") == 0){
        encodingSubtype = MIPS32_BRANCH;
        binOpcode = OP_BNE;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"BLEZ") == 0){
        binOpcode = OP_BLEZ;
        encodingType = MIPS32_I_FORMAT;
        encodingSubtype = MIPS32_BRANCHZ;
    }else if (strcmp(opcode,"BEQ") == 0){
        binOpcode = OP_BEQ;
        encodingType = MIPS32_I_FORMAT;
        encodingSubtype = MIPS32_BRANCH;
    }else if (strcmp(opcode,"BGTZ") == 0){
        binOpcode = OP_BGTZ;
        encodingType = MIPS32_I_FORMAT;
        encodingSubtype = MIPS32_BRANCHZ;
    }else if (strcmp(opcode,"JAL") == 0){
        encodingSubtype = MIPS32_JUMP;
        binOpcode = OP_JAL;
        encodingType = MIPS32_J_FORMAT;
    }else if (strcmp(opcode,"J") == 0){
        encodingSubtype = MIPS32_JUMP;
        binOpcode = OP_J;
        encodingType = MIPS32_J_FORMAT;
    }else if (strcmp(opcode,"LW") == 0){
        encodingSubtype = MIPS32_LOADSTORE;
        binOpcode = OP_LW;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"LHI") == 0){
        binOpcode = OP_LHI;
        encodingSubtype = MIPS32_LOADI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"LLO") == 0){
        binOpcode = OP_LLO;
        encodingSubtype = MIPS32_LOADI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"SRL") == 0){
        function = 2;
        encodingSubtype = MIPS32_SHIFT;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"SUB") == 0){
        function = 34;
        encodingSubtype = MIPS32_ARITHLOG;
        encodingType = MIPS32_R_FORMAT;
    }else if (strcmp(opcode,"SW") == 0){
        binOpcode = OP_SW;
        encodingSubtype = MIPS32_LOADSTORE;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"ORI") == 0){
        binOpcode = OP_ORI;
        encodingSubtype = MIPS32_ARITHLOGI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"XORI") == 0){
        binOpcode = OP_XORI;
        encodingSubtype = MIPS32_ARITHLOGI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"ANDI") == 0){
        binOpcode = OP_ANDI;
        encodingSubtype = MIPS32_ARITHLOGI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"ADDI") == 0){
        binOpcode = OP_ADDI;
        encodingSubtype = MIPS32_ARITHLOGI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"ADDIU") == 0){
        binOpcode = OP_ADDIU;
        encodingSubtype = MIPS32_ARITHLOGI;
        encodingType = MIPS32_I_FORMAT;
    }else if (strcmp(opcode,"SLL") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFT;
    }else if (strcmp(opcode,"SRA") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFT;
    }else if (strcmp(opcode,"SLLV") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFTV;
    }else if (strcmp(opcode,"SRAV") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFTV;
    }else if (strcmp(opcode,"SRL") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFTV;
    }else if (strcmp(opcode,"SRLV") == 0){
        binOpcode = OP_ALU;
        encodingType = MIPS32_R_FORMAT;
        encodingSubtype = MIPS32_SHIFTV;
    }else if (strcmp(opcode,"HALT") == 0){
        // Fake instruction to end execution
        bytes = new unsigned char[4];
        bytes[0] = 255;
        bytes[1] = 255;
        bytes[2] = 255;
        bytes[3] = 255;
        encodingType = MIPS32_NO_FORMAT;
        encodingSubtype = MIPS32_NO_SUBFORMAT;
        rawInstruction = new MemoryChunk(bytes,4);
    }else{
        throw new IllegalInstructionSyntaxException("Illegal opcode");
    }
    if (encodingType == MIPS32_R_FORMAT){
        if (encodingSubtype == MIPS32_ARITHLOG){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 ARITHLOG instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterOne = decodeRegisterOperand(operands[1]);
            sourceRegisterTwo = decodeRegisterOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_DIVMULT){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 DIVMULT instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
        }else if (encodingSubtype == MIPS32_SHIFT){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 SHIFT instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            shiftAmmount = decodeIntOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_SHIFTV){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 SHIFTV instruction");
            }
            destinationRegister = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            sourceRegisterOne = decodeRegisterOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_JUMPR || encodingSubtype == MIPS32_MOVETO){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 JUMPR - MOVETO instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
        }else if (encodingSubtype == MIPS32_MOVEFROM){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 MOVEFROM instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
        }
        bytes = new unsigned char[4];
        bytes[0] = ((binOpcode & 0x003F) << 2) | ((sourceRegisterOne & 0x0018) >> 3);
        bytes[1] = ((sourceRegisterOne & 0x0007) << 5) | (sourceRegisterTwo & 0x001F);
        bytes[2] = ((destinationRegister & 0x001F) << 3) | ((shiftAmmount & 0x001C) >> 2); 
        bytes[3] = ((shiftAmmount & 0x0003) << 6) | (function & 0x003F);
        rawInstruction = new MemoryChunk(bytes,4);
    }else if (encodingType == MIPS32_I_FORMAT){
        if (encodingSubtype == MIPS32_ARITHLOGI){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 ARITHLOGI instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            sourceRegisterOne = decodeRegisterOperand(operands[1]);
            immediate = decodeIntOperand(operands[2]);
        }else if (encodingSubtype == MIPS32_LOADI){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 LOADI instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            immediate = decodeIntOperand(operands[1]);
        }else if (encodingSubtype == MIPS32_BRANCH){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 BRANCH instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            sourceRegisterTwo = decodeRegisterOperand(operands[1]);
            immediate = decodeLabelOperand(operands[2],loader);
        }else if (encodingSubtype == MIPS32_BRANCHZ){
            if (operandsLength < 2){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 BRANCHZ instruction");
            }
            sourceRegisterOne = decodeRegisterOperand(operands[0]);
            immediate = decodeLabelOperand(operands[1],loader);
        }else if (encodingSubtype == MIPS32_LOADSTORE){
            if (operandsLength < 3){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 LOADSTORE instruction");
            }
            sourceRegisterTwo = decodeRegisterOperand(operands[0]);
            immediate = decodeIntOperand(operands[1]);
            sourceRegisterOne = decodeRegisterOperand(operands[2]);
        }
        bytes = new unsigned char[4];
        bytes[0] = ((binOpcode & 0x003F) << 2) | ((sourceRegisterOne & 0x0018) >> 3);
        bytes[1] = ((sourceRegisterOne & 0x0007) << 5) | (sourceRegisterTwo & 0x001F);
        bytes[2] = (immediate & 0xFF00) >> 8;
        bytes[3] = (immediate & 0x00FF);
        rawInstruction = new MemoryChunk(bytes,4);
    }else if (encodingType == MIPS32_J_FORMAT){
        if (encodingSubtype == MIPS32_JUMP){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 JUMP instruction");
            }
            immediate = decodeLabelOperand(operands[0],loader);
        }else if (encodingSubtype == MIPS32_TRAP){
            if (operandsLength < 1){
                throw new IllegalInstructionSyntaxException("Incorrect number of arguments for MIPS32 TRAP instruction");
            }
            immediate = decodeIntOperand(operands[0]);
        }
        bytes = new unsigned char[4];
        bytes[0] = ((binOpcode & 0x003F) << 2) | ((immediate & 0x03000000) >> 10);
        bytes[1] = (immediate & 0xFF00) >> 16;
        bytes[2] = (immediate & 0x00FF00) >> 8;
        bytes[3] = (immediate & 0x0000FF);
        rawInstruction = new MemoryChunk(bytes,4);
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
    return rawInstruction;
}

Instruction* MIPS32ISA::decodeInstruction(MemoryChunk* rawInst){
    if (rawInst->getBytesLength() != 4){
        throw new IllegalInstructionLengthException("MIPS32ISA instructions are 4 bytes long");
    }else{
        InstructionEncodingType encodingType;
        MIPS32_InstructionEncodingSubtype encodingSubtype;
    
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
                // Calculate function and use it to decode further
                function = 0x3F & bytes[3];
                encodingType = MIPS32_R_FORMAT;
                switch(function){
                    /* Calculate encoding subtype given function number */
                    case MIPS32FUNCTION_ADD: 
                    case MIPS32FUNCTION_ADDU:
                    case MIPS32FUNCTION_AND:
                    case MIPS32FUNCTION_NOR:
                    case MIPS32FUNCTION_OR:
                    case MIPS32FUNCTION_SUB:
                    case MIPS32FUNCTION_SUBU:
                    case MIPS32FUNCTION_XOR:
                        encodingSubtype = MIPS32_ARITHLOG;
                        break;
                    case MIPS32FUNCTION_DIV:
                    case MIPS32FUNCTION_DIVU:
                    case MIPS32FUNCTION_MULT:
                    case MIPS32FUNCTION_MULTU:
                        encodingSubtype = MIPS32_DIVMULT;
                        break;
                    case MIPS32FUNCTION_SLL:
                    case MIPS32FUNCTION_SRA:
                    case MIPS32FUNCTION_SRL:
                        encodingSubtype = MIPS32_SHIFT;
                        break;
                    case MIPS32FUNCTION_SLLV:
                    case MIPS32FUNCTION_SRAV:
                    case MIPS32FUNCTION_SRLV:
                        encodingSubtype = MIPS32_SHIFTV;
                        break;
                    case MIPS32FUNCTION_JALR:
                    case MIPS32FUNCTION_JR:
                        encodingSubtype = MIPS32_JUMPR;
                        break;
                    case MIPS32FUNCTION_MFHI:
                    case MIPS32FUNCTION_MFLO:
                        encodingSubtype = MIPS32_MOVEFROM;
                        break;
                    case MIPS32FUNCTION_MTHI:
                    case MIPS32FUNCTION_MTLO:
                        encodingSubtype = MIPS32_MOVETO;
                        break;
                }
                break; // End R format
            case OP_ADDI:
            case OP_ADDIU:
            case OP_ANDI:
            case OP_ORI:
            case OP_XORI:
            case OP_SLTI:
            case OP_SLTIU:
                encodingType = MIPS32_I_FORMAT;
                encodingSubtype = MIPS32_ARITHLOGI;
                break;
            case OP_LLO:
            case OP_LHI:
                encodingType = MIPS32_I_FORMAT;
                encodingSubtype = MIPS32_LOADI;
                break;
            case OP_BEQ:
            case OP_BNE:
                encodingType = MIPS32_I_FORMAT;
                encodingSubtype = MIPS32_BRANCH;
                break;
            case OP_BGTZ:
            case OP_BLEZ:
                encodingType = MIPS32_I_FORMAT;
                encodingSubtype = MIPS32_BRANCHZ;
                break;
            case OP_LB:
            case OP_LBU:
            case OP_LH:
            case OP_LHU:
            case OP_LW:
            case OP_SB:
            case OP_SH:
            case OP_SW:
                encodingType = MIPS32_I_FORMAT;
                encodingSubtype = MIPS32_LOADSTORE;
                break;
            case OP_J:
            case OP_JAL:
                encodingType = MIPS32_J_FORMAT;
                encodingSubtype = MIPS32_JUMP;
                break;
            case 63: // Syscall
                inst = new Instruction();
                break;
        }
        // Add specific encoding info
        if (encodingType == MIPS32_J_FORMAT){
            /* Jump Instruction format: ooooooii iiiiiiii iiiiiiii iiiiiiii*/
            immediate = 
                        (((bytes[0] & 0x03) << 24) | 
                          (bytes[1] << 16) | 
                          (bytes[2] << 8) | 
                          (bytes[3]));
            if (encodingSubtype == MIPS32_JUMP){
                inst = new JumpInstruction();
                sourceOperandOne = new ImmediateOperand(immediate);
                destinationOperand = new SpecialRegisterOperand(SPECIAL_REGISTER_PC);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(destinationOperand,1);
            }// else if encodingSubtype == MIPS32_TRAP
            
        }else if (encodingType == MIPS32_I_FORMAT){
            /* Immediate format: ooooooss sssttttt iiiiiiii iiiiiiii*/
            sourceRegisterOne = ((0x3 & bytes[0]) << 3) | ((0xE0 & bytes[1]) >> 5);
            sourceRegisterTwo = 0x1F & bytes[1];
            immediate = ((bytes[2]) << 8) | bytes[3];
            
            if (encodingSubtype == MIPS32_ARITHLOGI){
                switch(opcode){
                    case OP_ADDI:
                        aluFunction = ALU_FUNCTION_INT_ADD; break;
                    case OP_ADDIU:
                        aluFunction = ALU_FUNCTION_INT_ADD_UNSIGNED; break;
                    case OP_ANDI:
                        aluFunction = ALU_FUNCTION_AND; break;
                    case OP_ORI:
                        aluFunction = ALU_FUNCTION_OR; break;
                    case OP_XORI:
                        aluFunction = ALU_FUNCTION_XOR; break;
                    case OP_SLTI:
                        // aluFunction = ?? break;
                    case OP_SLTIU:
                        // aluFunction = ?? 
                        break;
                }
                
                inst = new ALUInstruction(3,aluFunction);
                sourceOperandOne = new RegisterOperand(sourceRegisterOne, REGISTER_TYPE_INT);
                sourceOperandTwo = new ImmediateOperand(immediate);
                destinationOperand = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(sourceOperandTwo,1);
                inst->setOperand(destinationOperand,2);
                // End encoding subytype ARIGHTLOGI
                
            }else if (encodingSubtype == MIPS32_LOADI){
                switch(opcode){
                    case OP_LLO:
                        aluFunction = ALU_FUNCTION_MOV_LOWER_16_BITS;
                        break;
                    case OP_LHI:
                        aluFunction = ALU_FUNCTION_MOV_UPPER_16_BITS;
                        break;
                }
                inst = new ALUInstruction(3,aluFunction);
                sourceOperandOne = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                sourceOperandTwo = new ImmediateOperand(immediate);
                destinationOperand = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(sourceOperandTwo,1);
                inst->setOperand(destinationOperand,2);
                // end encodingSubtype LOADI
            }else if (encodingSubtype == MIPS32_BRANCH){
                ConditionType conditionType;
                switch(opcode){
                    case OP_BEQ:
                        conditionType = CONDITION_TYPE_EQUALS;
                        break;
                    case OP_BNE:
                        conditionType = CONDITION_TYPE_NOT_EQUALS;
                        break;
                        // Other options not possible
                }
                BranchInstruction* branchInst = new BranchInstruction();
                inst = branchInst;
                branchInst->setConditionType(conditionType);
                // MIPS32_BRANCH subtype use two registers
                branchInst->setFirstComparator(new RegisterOperand(sourceRegisterOne,REGISTER_TYPE_INT));
                branchInst->setSecondComparator(new RegisterOperand(sourceRegisterTwo,REGISTER_TYPE_INT));
                branchInst->setPCValueTakenOperand(new ImmediateOperand(immediate));
                branchInst->setPCValueNotTakenOperand(new SpecialRegisterOperand(SPECIAL_REGISTER_PC));
                branchInst->setDestinationOperand(0,new SpecialRegisterOperand(SPECIAL_REGISTER_PC));
            }else if (encodingSubtype == MIPS32_BRANCHZ){
                ConditionType conditionType;
                switch(opcode){
                    case OP_BLEZ:
                        conditionType = CONDITION_TYPE_LESS_THAN_OR_EQUALS;
                        break;
                    case OP_BGTZ:
                        conditionType = CONDITION_TYPE_GREATER;
                        break;
                        // Other options not possible
                }
                BranchInstruction* branchInst = new BranchInstruction();
                inst = branchInst;
                branchInst->setConditionType(conditionType);
                // MIPS32_BRANCH subtype use two registers
                branchInst->setFirstComparator(new RegisterOperand(sourceRegisterOne,REGISTER_TYPE_INT));
                branchInst->setSecondComparator(new RegisterOperand(sourceRegisterTwo,REGISTER_TYPE_INT));
                branchInst->setPCValueTakenOperand(new ImmediateOperand(immediate));
                branchInst->setPCValueNotTakenOperand(new SpecialRegisterOperand(SPECIAL_REGISTER_PC));
                branchInst->setDestinationOperand(0,new SpecialRegisterOperand(SPECIAL_REGISTER_PC));
            }else if (encodingSubtype == MIPS32_LOADSTORE){
                int loadStoreSize = -1; // How many bytes are going to be read or written
                MessageType loadStore;
                switch(opcode){
                    case OP_LB:
                    case OP_LBU:
                        loadStore = MEMORY_REQUEST_MEMORY_READ;
                        loadStoreSize = 1;
                        break;
                    case OP_SB:
                        loadStore = MEMORY_REQUEST_MEMORY_WRITE;
                        loadStoreSize = 1;
                        break;
                    case OP_LH:
                    case OP_LHU:
                        loadStore = MEMORY_REQUEST_MEMORY_READ;
                        loadStoreSize = 2;
                        break;                        
                    case OP_SH:
                        loadStore = MEMORY_REQUEST_MEMORY_WRITE;
                        loadStoreSize = 2;
                        break;
                    case OP_LW:
                        loadStore = MEMORY_REQUEST_MEMORY_READ;
                        loadStoreSize = 4;
                        break;
                    case OP_SW:
                        loadStore = MEMORY_REQUEST_MEMORY_WRITE;
                        loadStoreSize = 4;
                        break;
                }
                LoadStoreInstruction* loadInst = new LoadStoreInstruction(loadStore, loadStoreSize);
                inst = loadInst;
                sourceOperandOne = new IndexedOperand(immediate, sourceRegisterOne);
                sourceOperandTwo = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                loadInst->setAddressOperand(sourceOperandOne);
                loadInst->setReadWriteOperand(sourceOperandTwo);
            }
            
        }else if (encodingType == MIPS32_R_FORMAT){
            /* Register Format:  ooooooss sssttttt dddddaaa aaffffff */
            sourceRegisterOne = ((0x3 & bytes[0]) << 3) | ((0xE0 & bytes[1]) >> 5);
            sourceRegisterTwo = 0x1F & bytes[1];
            destinationRegister = (0xF8 & bytes[2]) >> 3;
            shiftAmmount = ((0x07 & bytes[2]) << 2) | ((0xC0 & bytes[3]) >> 6);
            /* Check if function binary is legal*/
            switch (function){
                case MIPS32FUNCTION_SLL:  /* sll */
                    aluFunction = ALU_FUNCTION_SHIFT_LEFT; break;
                case MIPS32FUNCTION_SRL:  /* srl */
                    aluFunction = ALU_FUNCTION_SHIFT_RIGHT_LOGICAL; break; 
                case MIPS32FUNCTION_SRA:  /* sra */
                    aluFunction = ALU_FUNCTION_SHIFT_RIGHT_ARITHMETIC; break;
                case MIPS32FUNCTION_SLLV:  /* sllv */
                    aluFunction = ALU_FUNCTION_SHIFT_LEFT; break;
                case MIPS32FUNCTION_SRLV:  /* srlv */
                    aluFunction = ALU_FUNCTION_SHIFT_RIGHT_LOGICAL; break;
                case MIPS32FUNCTION_SRAV:  /* srav */
                    aluFunction = ALU_FUNCTION_SHIFT_RIGHT_ARITHMETIC; break;
                case MIPS32FUNCTION_MFHI: /* mfhi */
                case MIPS32FUNCTION_MTHI: /* mthi */
                case MIPS32FUNCTION_MFLO: /* mflo */
                case MIPS32FUNCTION_MTLO: /* mtlo */
                    aluFunction = ALU_FUNCTION_MOV; break;
                case MIPS32FUNCTION_MULT: /* mult */
                case MIPS32FUNCTION_MULTU: /* multu */
                case MIPS32FUNCTION_DIV: /* div */
                case MIPS32FUNCTION_DIVU: /* divu */
                    // Multiplier function
                    break;
                case MIPS32FUNCTION_ADD: /* add */
                    aluFunction = ALU_FUNCTION_INT_ADD; break; 
                case MIPS32FUNCTION_ADDU: /* addu */
                    aluFunction = ALU_FUNCTION_INT_ADD_UNSIGNED; break;
                case MIPS32FUNCTION_SUB: /* sub */ 
                    aluFunction = ALU_FUNCTION_INT_SUB; break;
                case MIPS32FUNCTION_SUBU: /* subu */
                    aluFunction = ALU_FUNCTION_INT_SUB_UNSIGNED; break;
                case MIPS32FUNCTION_AND: /* and */
                    aluFunction = ALU_FUNCTION_AND; break;
                case MIPS32FUNCTION_OR: /* or */
                    aluFunction = ALU_FUNCTION_OR; break;
                case MIPS32FUNCTION_XOR: /* xor */
                    aluFunction = ALU_FUNCTION_XOR; break;
                case MIPS32FUNCTION_NOR: /* nor */
                    aluFunction = ALU_FUNCTION_NOR; break;
                case MIPS32FUNCTION_SLTU: /* sltu */
                case MIPS32FUNCTION_SLT: /* slt */
                    break;
                case MIPS32FUNCTION_JALR:
                case MIPS32FUNCTION_JR:
                    break;
                default:
                    throw new IllegalInstructionBinaryException("Illegal MIPS32 instruction ALU function");
            }
            
            if (encodingSubtype == MIPS32_ARITHLOG){
                inst = new ALUInstruction(3,aluFunction);
                sourceOperandOne = new RegisterOperand(sourceRegisterOne, REGISTER_TYPE_INT);
                sourceOperandTwo = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                destinationOperand = new RegisterOperand(destinationRegister, REGISTER_TYPE_INT);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(sourceOperandTwo,1);
                inst->setOperand(destinationOperand,2);
            }else if (encodingSubtype == MIPS32_SHIFT){
                inst = new ALUInstruction(3,aluFunction);
                sourceOperandOne = new RegisterOperand(sourceRegisterTwo, REGISTER_TYPE_INT);
                sourceOperandTwo = new ImmediateOperand(shiftAmmount);
                destinationOperand = new RegisterOperand(destinationRegister, REGISTER_TYPE_INT);
                inst->setOperand(sourceOperandOne,0);
                inst->setOperand(sourceOperandTwo,1);
                inst->setOperand(destinationOperand,2);
            }
            
        } // No else 
        
        // Pass again and set Archetype
        switch(opcode){
            case 0:
                switch (function){
                    case 0:  /* sll */
                        archetype = sll_; break;
                    case 2:  /* srl */
                        archetype = srl_; break;
                    case 3:  /* sra */
                        archetype = sra_; break;
                    case 4:  /* sllv */
                        archetype = sllv_; break;
                    case 6:  /* srlv */
                        archetype = srlv_; break;
                    case 7:  /* srav */
                        archetype = srav_; break;
                    case 16: /* mfhi */
                    case 17: /* mthi */
                    case 18: /* mflo */
                    case 19: /* mtlo */
                         break;
                    case 24: /* mult */
                    case 25: /* multu */
                    case 26: /* div */
                    case 27: /* divu */
                    case 32: /* add */
                        archetype = add_; break; 
                    case 33: /* addu */
                    case 34: /* sub */
                        archetype = sub_; break;
                    case 35: /* subu */
                    case 36: /* and */
                        archetype = and_; break;
                    case 37: /* or */
                        archetype = or_; break;
                    case 38: /* xor */
                        archetype = xor_; break;
                    case 39: /* nor */
                    case 41: /* sltu */
                    case 42: /* slt */
                        break;
                }
                break;
            case OP_ADDI:
                archetype = addi_; break;
            case OP_ADDIU:
                archetype = addiu_; break;
            case OP_ANDI:
                archetype = andi_; break;
            case OP_ORI:
                archetype = ori_; break;
            case OP_XORI:
                archetype = xori_; break;
            case OP_SLTI:
                // archetype = slti_; break;
            case OP_SLTIU:
                //archetype = sltiu_; break;
            case OP_LLO:
                archetype = llo_; break;
            case OP_LHI:
                archetype = lhi_; break;
            case OP_BEQ:
                archetype = beq_; break;
            case OP_BNE:
                archetype = bne_; break;
            case OP_BGTZ:
                archetype = bgtz_; break;
            case OP_BLEZ:
                archetype = blez_; break;
            case OP_LB:
                archetype = lb_; break;
            case OP_LBU:
                archetype = lbu_; break;
            case OP_LH:
                archetype = lh_; break;
            case OP_LHU:
                archetype = lhu_; break;
            case OP_LW:
                archetype = lw_; break;
            case OP_SB:
                archetype = sb_; break;
            case OP_SH:
                archetype = sh_; break;
            case OP_SW:
                archetype = sw_; break;
            case OP_J:
                //archetype = j_; break;
            case OP_JAL:
                archetype = jal_; break;
            case 63: // Syscall
                archetype = syscall_; break;
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

bool MIPS32ISA::isLittleEndian(){
    return true;
}
