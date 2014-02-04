/* 
 * File:   MIPS32ISA.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 06:58 PM
 */

#ifndef MIPS32ISA_H
#define	MIPS32ISA_H

#define MIPS32REGISTERCOUNT 64

#include "Instruction.h"
#include "StaticInstruction.h"
#include "ISA.h"
#include "../memory/MemoryChunk.h"


class MIPS32ISA : public ISA{
private:
    static MIPS32ISA* instance;
    
    /* INT_ALU Instructions */
    StaticInstruction* add_;
    StaticInstruction* nop_;
    StaticInstruction* and_;
    StaticInstruction* or_;
    StaticInstruction* li_;
    StaticInstruction* sub_;
    StaticInstruction* sll_;
    StaticInstruction* srl_;
    
    /* READ_MODIFY_WRITE Instructions (for semaphore implementation) */
    StaticInstruction* ll_;
    StaticInstruction* sc_;
    
    /* JUMP_BRANCH Instrucitons */
    StaticInstruction* jal_;
    StaticInstruction* jalr_;
    StaticInstruction* bne_;
    StaticInstruction* bnez_;
    
    /* LOAD_STORE Instructions */
    StaticInstruction* lw_;
    StaticInstruction* sw_;
    MIPS32ISA();
public:
    static MIPS32ISA* getInstance();
    Instruction* buildInstruction(char* opcode, char** operands, int operandsLength);
    Instruction* decodeInstruction(MemoryChunk* rawInst);
    MemoryChunk* encodeInstruction(Instruction* inst);
};

enum InstructionEncodingType{
    MIPS32_R_FORMAT, /* Register Format:  ooooooss sssttttt dddddaaa aaffffff*/ 
    MIPS32_I_FORMAT, /* Immediate Format: ooooooss sssttttt iiiiiiii iiiiiiii*/
    MIPS32_J_FORMAT  /* Jump Format:      ooooooii iiiiiiii iiiiiiii iiiiiiii*/
};

enum MIPS32_InstructionEncodingSubtype{
    MIPS32_ARITHLOG,
    MIPS32_DIVMULT,
    MIPS32_SHIFT,
    MIPS32_SHIFTV,
    MIPS32_JUMPR,
    MIPS32_MOVEFROM,
    MIPS32_MOVETO,
    MIPS32_ARITHLOGI,
    MIPS32_LOADI,
    MIPS32_BRANCH,
    MIPS32_BRANCHZ,
    MIPS32_LOADSTORE,
    MIPS32_JUMP,
    MIPS32_TRAP
};

enum InstructionOpcode{ /* Matches Mnemonic text with instruction opcode */
    OP_ALU,              /* opcode: 000000b */
    NO_OP1,              /* opcode: 000001b */
    OP_J,                /* opcode: 000010b */
    OP_JAL,              /* opcode: 000011b */
    OP_BEQ,              /* opcode: 000100b */
    OP_BNE,              /* opcode: 000101b */
    OP_BLEZ,             /* opcode: 000110b */
    OP_BGTZ,             /* opcode: 000111b */
    OP_JR,               /* opcode: 001000b */
    OP_JALR,             /* opcode: 001001b */
    OP_SLTI,             /* opcode: 001010b */
    NO_OP11,             /* opcode: 001011b */
    OP_ANDI,             /* opcode: 001100b */
    OP_ORI,              /* opcode: 001101b */
    OP_XORI,             /* opcode: 001110b */
    NO_OP15,             /* opcode: 001111b */
    NO_OP16,             /* opcode: 010000b */
    NO_OP17,             /* opcode: 010001b */
    NO_OP18,             /* opcode: 010010b */
    NO_OP19,             /* opcode: 010011b */
    NO_OP20,             /* opcode: 010100b */
    NO_OP21,             /* opcode: 010101b */
    NO_OP22,             /* opcode: 010110b */
    NO_OP23,             /* opcode: 010111b */
    OP_LLI,              /* opcode: 011000b */
    OP_LLHI,             /* opcode: 011001b */
    OP_TRAP,             /* opcode: 011010b */
    NO_OP27,             /* opcode: 011011b */
    NO_OPZ8,             /* opcode: 011100b */
    NO_OP29,             /* opcode: 011101b */
    NO_OP30,             /* opcode: 011110b */
    NO_OP31,             /* opcode: 011111b */
    OP_LB,               /* opcode: 100000b */
    OP_LH,               /* opcode: 100001b */
    NO_OP34,             /* opcode: 100010b */
    OP_LW,               /* opcode: 100011b */
    OP_LBU,              /* opcode: 100100b */
    OP_LHU,              /* opcode: 100101b */
    NO_OP38,             /* opcode: 100110b */
    NO_OP39,             /* opcode: 100111b */
    OP_SB,               /* opcode: 101000b */
    OP_SH,               /* opcode: 101001b */
    NO_OP42,             /* opcode: 101010b */
    OP_SW,               /* opcode: 101011b */
    NO_OP44,             /* opcode: 101100b */
    NO_OP45,             /* opcode: 101101b */
    NO_OP46,             /* opcode: 101110b */
    NO_OP47,             /* opcode: 101111b */
    NO_OP48,             /* opcode: 110000b */
    NO_OP49,             /* opcode: 110001b */
    NO_OP50,             /* opcode: 110010b */
    NO_OP51,             /* opcode: 110011b */
    NO_OP52,             /* opcode: 110100b */
    NO_OP53,             /* opcode: 110101b */
    NO_OP54,             /* opcode: 110110b */
    NO_OP55,             /* opcode: 110111b */
    NO_OP56,             /* opcode: 111000b */
    NO_OP57,             /* opcode: 111001b */
    NO_OP58,             /* opcode: 111010b */
    NO_OP59,             /* opcode: 111011b */
    NO_OP60,             /* opcode: 111100b */
    NO_OP61,             /* opcode: 111101b */
    NO_OP62,             /* opcode: 111110b */
    NO_OP63,             /* opcode: 111111b */
};

#endif	/* MIPS32ISA_H */

