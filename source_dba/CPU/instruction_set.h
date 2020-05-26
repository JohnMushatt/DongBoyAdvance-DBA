//
// Created by johnm on 5/12/2020.
//

#ifndef DONGBOYADVANCE_INSTRUCTION_SET_H
#define DONGBOYADVANCE_INSTRUCTION_SET_H

#include "cpu.h"
#include "logger.h"

#define BIT0 1 << 0
#define BIT1 1 << 1
#define BIT2 1 << 2
#define BIT3 1 << 3
#define BIT4 1 << 4
#define BIT5 1 << 5
#define BIT6 1 << 6
#define BIT7 1 << 7
#define BIT8 1 << 8
#define BIT9 1 << 9
#define BIT10 1 << 10
#define BIT11 1 << 11
#define BIT12 1 << 12
#define BIT13 1 << 13
#define BIT14 1 << 14
#define BIT15 1 << 15
#define BIT16 1 << 16
#define BIT17 1 << 17
#define BIT18 1 << 18
#define BIT19 1 << 19
#define BIT20 1 << 20
#define BIT21 1 << 21
#define BIT22 1 << 22
#define BIT23 1 << 23
#define BIT24 1 << 24
#define BIT25 1 << 25
#define BIT26 1 << 26
#define BIT27 1 << 27
#define BIT28 1 << 28
#define BIT29 1 << 29
#define BIT30 1 << 30
#define BIT31 1 << 31



typedef enum {
    ADD, SUB, CMP
} Instruction_Type;
typedef struct _instruction {
    Instruction_Type type;
    ARM_U_WORD destination;
    ARM_U_WORD operand1;
    ARM_U_WORD operand2;
} Instruction;
/**
Opcode Format
  Bit    Expl.
  31-28  Condition
  27-26  Must be 00b for this instruction
  25     I - Immediate 2nd Operand Flag (0=Register, 1=Immediate)
  24-21  Opcode (0-Fh)               ;*=Arithmetic, otherwise Logical
           0: AND{cond}{S} Rd,Rn,Op2    ;AND logical       Rd = Rn AND Op2
           1: EOR{cond}{S} Rd,Rn,Op2    ;XOR logical       Rd = Rn XOR Op2
           2: SUB{cond}{S} Rd,Rn,Op2 ;* ;subtract          Rd = Rn-Op2
           3: RSB{cond}{S} Rd,Rn,Op2 ;* ;subtract reversed Rd = Op2-Rn
           4: ADD{cond}{S} Rd,Rn,Op2 ;* ;add               Rd = Rn+Op2
           5: ADC{cond}{S} Rd,Rn,Op2 ;* ;add with carry    Rd = Rn+Op2+Cy
           6: SBC{cond}{S} Rd,Rn,Op2 ;* ;sub with carry    Rd = Rn-Op2+Cy-1
           7: RSC{cond}{S} Rd,Rn,Op2 ;* ;sub cy. reversed  Rd = Op2-Rn+Cy-1
           8: TST{cond}{P}    Rn,Op2    ;test            Void = Rn AND Op2
           9: TEQ{cond}{P}    Rn,Op2    ;test exclusive  Void = Rn XOR Op2
           A: CMP{cond}{P}    Rn,Op2 ;* ;compare         Void = Rn-Op2
           B: CMN{cond}{P}    Rn,Op2 ;* ;compare neg.    Void = Rn+Op2
           C: ORR{cond}{S} Rd,Rn,Op2    ;OR logical        Rd = Rn OR Op2
           D: MOV{cond}{S} Rd,Op2       ;move              Rd = Op2
           E: BIC{cond}{S} Rd,Rn,Op2    ;bit clear         Rd = Rn AND NOT Op2
           F: MVN{cond}{S} Rd,Op2       ;not               Rd = NOT Op2
  20     S - Set Condition Codes (0=No, 1=Yes) (Must be 1 for opcode 8-B)
  19-16  Rn - 1st Operand Register (R0..R15) (including PC=R15)
              Must be 0000b for MOV/MVN.
  15-12  Rd - Destination Register (R0..R15) (including PC=R15)
              Must be 0000b (or 1111b) for CMP/CMN/TST/TEQ{P}.
  When above Bit 25 I=0 (Register as 2nd Operand)
    When below Bit 4 R=0 - Shift by Immediate
      11-7   Is - Shift amount   (1-31, 0=Special/See below)
    When below Bit 4 R=1 - Shift by Register
      11-8   Rs - Shift register (R0-R14) - only lower 8bit 0-255 used
      7      Reserved, must be zero  (otherwise multiply or LDREX or undefined)
    6-5    Shift Type (0=LSL, 1=LSR, 2=ASR, 3=ROR)
    4      R - Shift by Register Flag (0=Immediate, 1=Register)
    3-0    Rm - 2nd Operand Register (R0..R15) (including PC=R15)
  When above Bit 25 I=1 (Immediate as 2nd Operand)
    11-8   Is - ROR-Shift applied to nn (0-30, in steps of 2)
    7-0    nn - 2nd Operand Unsigned 8bit Immediate
   */
typedef union _opcode_ALU {
    ARM_U_WORD word;
    struct {
        ARM_U_WORD nn : 8; //nn - 2nd Operand Unsigned 8bit Immediate
        ARM_U_WORD Is : 4;
        ARM_U_WORD Rm;
    };
} Opcode_ALU;
typedef enum {
    EQ, NE, CS, HS, CC, LO, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL
} Branch_Condition;

void decode(ARM_U_WORD opcode);

void Logical_MOV(ARM_U_WORD reg_d, ARM_U_WORD op2);

void Logical_MVN(ARM_U_WORD reg_d, ARM_U_WORD op2);

/**
 * Arithmetic Instructions
 */
//TODO VERY IMPORTANT, THESE INSTRUCTIONS NEED TO UPDATE NZCV FLAGS!!
/**
 * @todo Verify that add, addc, sub, and cmp correctly update flags
 * @body Verify that the above functions correctly modify status flags
 */
void Arithmetic_ADD(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD op2);

void Arithmetic_ADDC(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD op2);

void Arithmetic_SUB(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD op2);
/**
 * AND Instructions
 */
//2nd operand is immediate version
void Arithmetic_AND_Immediate(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD immediate);

void Arithmetic_ANDS_Immediate(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD immediate);

//2nd operand is register
void Arithmetic_AND_Register(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n);

void Arithmetic_ANDS_Register(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n);

//2nd operand is register-shifted value
void Arithmetic_AND_Register_Shifted(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD reg_n_offset);

void Arithmetic_ANDS_Register_Shifted(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD reg_n_offset);

void Jump_Branch(Branch_Condition condition, ARM_U_WORD label);

bool check_condition(Branch_Condition condition);


void software_interrupt(ARM_U_WORD opcode);
void CoRegTrans(ARM_U_WORD opcode);
void CoDataOp(ARM_U_WORD opcode);
void CoDataTrans(ARM_U_WORD opcode);
void Branch(ARM_U_WORD opcode);
void BlockTrans(ARM_U_WORD opcode);
void TransReg9(ARM_U_WORD opcode);
void TransImm9(ARM_U_WORD opcode);
void TransImm10(ARM_U_WORD opcode);
void TransReg10(ARM_U_WORD opcode);
void TransSwp12(ARM_U_WORD opcode);
void unknown_opcode(ARM_U_WORD opcode);
void undefined_opcode(ARM_U_WORD opcode);
/**
 * @todo Check to see if CMP correctly sets overflow and carry flags
 * @body Make sure CMP correctly sets the properly flags when there is
 * a overflow/carry result
 */
void Arithmetic_CMP(ARM_U_WORD reg_d, ARM_U_WORD op2, bool immediate);


/**
 * Update the condition flags from the given ARM_U_WORD (uint32_t)
 */
void update_condition_flags(ARM_U_WORD flags);

#endif //DONGBOYADVANCE_INSTRUCTION_SET_H
