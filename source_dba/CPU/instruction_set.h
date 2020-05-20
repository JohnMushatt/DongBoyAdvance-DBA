//
// Created by johnm on 5/12/2020.
//

#ifndef DONGBOYADVANCE_INSTRUCTION_SET_H
#define DONGBOYADVANCE_INSTRUCTION_SET_H

#include "cpu.h"
#include "logger.h"


typedef enum {
    ADD, SUB, CMP
} Instruction_Type;
typedef struct _instruction {
    Instruction_Type type;
    ARM_U_WORD destination;
    ARM_U_WORD operand1;
    ARM_U_WORD operand2;
} Instruction;
typedef enum {
    EQ, NE, CS, HS, CC, LO, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL
} Branch_Condition;

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
