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
    ARM_WORD left;
    ARM_WORD right;
} Instruction;

void Logical_MOV(ARM_WORD reg_d, ARM_WORD op2);

void Logical_MVN(ARM_WORD reg_d, ARM_WORD op2);

/**
 * Arithmetic Instructions
 */
//TODO VERY IMPORTANT, THESE INSTRUCTIONS NEED TO UPDATE NZCV FLAGS!!
/**
 * @todo Verify that add, addc, sub, and cmp correctly update flags
 * @body Verify that the above functions correctly modify status flags
 */
void Arithmetic_ADD(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);

void Arithmetic_ADDC(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);

void Arithmetic_SUB(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);
/**
 * AND Instructions
 */
//2nd operand is immediate version
void Arithmetic_AND_Immediate(ARM_WORD dest, ARM_WORD reg_d, ARM_WORD immediate);

void Arithmetic_ANDS_Immediate(ARM_WORD dest, ARM_WORD reg_d, ARM_WORD immediate);

//2nd operand is register
void Arithmetic_AND_Register(ARM_WORD dest, ARM_WORD reg_d);

void Arithmetic_ANDS_Register(ARM_WORD dest, ARM_WORD reg_d);

//2nd operand is register-shifted register
void Arithmetic_AND_Register_Shifted(ARM_WORD dest, ARM_WORD reg_d, ARM_WORD reg_n_offset);

void Arithmetic_ANDS_Register_Shifted(ARM_WORD dest, ARM_WORD reg_d, ARM_WORD reg_n_offset);

/**
 * @todo Check to see if CMP correctly sets overflow and carry flags
 * @body Make sure CMP correctly sets the properly flags when there is
 * a overflow/carry result
 */
void Arithmetic_CMP(ARM_WORD reg_d, ARM_WORD op2, bool immediate);


/**
 * Update the condition flags from the given ARM_WORD (uint32_t)
 */
void update_condition_flags(ARM_WORD flags);

#endif //DONGBOYADVANCE_INSTRUCTION_SET_H
