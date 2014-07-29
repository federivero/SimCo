/* 
 * File:   MIPS32ISA.h
 * Author: fede
 *
 * Created on 23 de enero de 2014, 06:58 PM
 */

#ifndef MIPS32ISA_H
#define	MIPS32ISA_H

#define MIPS32REGISTERCOUNT 32
#define MIPS_32_INTEGER_REGISTER_COUNT 34 // 32 Programable registers + hi + lo
#define MIPS_32_FLOATING_POINT_REGISTER_COUNT 0
#define MIPS_32_INSTRUCTION_LENGTH 4

#include "Instruction.h"
#include "StaticInstruction.h"
#include "ISA.h"
#include "../memory/MemoryChunk.h"


class MIPS32ISA : public ISA{
private:
    static MIPS32ISA* instance;
    
    /* INT_ALU Instructions */
    StaticInstruction* add_, *nop_, *and_, *or_, *li_, *sub_, *sll_, *sllv_, *sra_, 
            *srl_, *srav_, *srlv_, *xor_, *llo_, *lhi_, *xori_, *ori_, *andi_, *addi_, *addiu_;
            
    /* READ_MODIFY_WRITE Instructions (for semaphore implementation) */
    StaticInstruction* ll_, *sc_;
    
    /* JUMP_BRANCH Instrucitons */
    StaticInstruction* jal_, *jalr_, *bne_, *bnez_;
    
    /* LOAD_STORE Instructions */
    StaticInstruction* lw_, *sw_, *lb_, *lbu_, *lh_, *lhu_, *sb_, *sh_;
    
    /* Fake instruction to end execution */
    StaticInstruction* syscall_;
    
    MIPS32ISA();
public:
    static MIPS32ISA* getInstance();
    MemoryChunk* buildInstruction(char* opcode, char** operands, int operandsLength);
    Instruction* decodeInstruction(MemoryChunk* rawInst);
    MemoryChunk* encodeInstruction(Instruction* inst);
    RegisterFile* createArchitectedRegisterFile();
    bool isLittleEndian();
    int getInstructionLength();
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
    OP_ADDI,             /* opcode: 001000b */
    OP_ADDIU,            /* opcode: 001001b */
    OP_SLTI,             /* opcode: 001010b */
    OP_SLTIU,            /* opcode: 001011b */
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
    OP_LLO,              /* opcode: 011000b */
    OP_LHI,              /* opcode: 011001b */
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

enum MIPS32_ALU_FUNCTION{
    MIPS32FUNCTION_SLL,   /* 000000 */
    NOFUNCTION1,          /* 000001 */
    MIPS32FUNCTION_SRL,   /* 000010 */
    MIPS32FUNCTION_SRA,   /* 000011 */
    MIPS32FUNCTION_SLLV,  /* 000100 */
    NOFUNCTION2,          /* 000101 */
    MIPS32FUNCTION_SRLV,  /* 000110 */
    MIPS32FUNCTION_SRAV,  /* 000111 */
    MIPS32FUNCTION_JR,    /* 001000 */
    MIPS32FUNCTION_JALR,  /* 001001 */
    NOFUNCTION3,          /* 001010 */
    NOFUNCTION4,          /* 001011 */
    NOFUNCTION5,          /* 001100 */
    NOFUNCTION6,          /* 001101 */
    NOFUNCTION7,          /* 001110 */
    NOFUNCTION8,          /* 001111 */
    MIPS32FUNCTION_MFHI,  /* 010000 */
    MIPS32FUNCTION_MTHI,  /* 010001 */
    MIPS32FUNCTION_MFLO,  /* 010010 */
    MIPS32FUNCTION_MTLO,  /* 010011 */
    NOFUNCTION9,          /* 010100 */
    NOFUNCTION10,         /* 010101 */
    NOFUNCTION11,         /* 010110 */
    NOFUNCTION12,         /* 010111 */
    MIPS32FUNCTION_MULT,  /* 011000 */
    MIPS32FUNCTION_MULTU, /* 011001 */
    MIPS32FUNCTION_DIV,   /* 011010 */
    MIPS32FUNCTION_DIVU,  /* 011011 */
    NOFUNCTION13,         /* 011100 */
    NOFUNCTION14,         /* 011101 */
    NOFUNCTION15,         /* 011110 */
    NOFUNCTION16,         /* 011111 */
    MIPS32FUNCTION_ADD,   /* 100000 */
    MIPS32FUNCTION_ADDU,  /* 100001 */
    MIPS32FUNCTION_SUB,   /* 100010 */
    MIPS32FUNCTION_SUBU,  /* 100011 */
    MIPS32FUNCTION_AND,   /* 100100 */
    MIPS32FUNCTION_OR,    /* 100101 */
    MIPS32FUNCTION_XOR,   /* 100110 */
    MIPS32FUNCTION_NOR,   /* 100111 */
    NOFUNCTION17,         /* 100000 */
    NOFUNCTION18,         /* 100001 */
    MIPS32FUNCTION_SLT,   /* 100010 */
    MIPS32FUNCTION_SLTU   /* 100011 */
};

#endif	/* MIPS32ISA_H */

