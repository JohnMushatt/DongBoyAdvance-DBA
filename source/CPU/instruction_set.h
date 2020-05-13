//
// Created by johnm on 5/12/2020.
//

#ifndef DONGBOYADVANCE_INSTRUCTION_SET_H
#define DONGBOYADVANCE_INSTRUCTION_SET_H

#include "cpu.h"
#include "logger.h"


typedef enum {
    ADD,SUB,CMP
} Instruction_Type;
typedef struct _instruction {
    Instruction_Type type;
    ARM_WORD  left;
    ARM_WORD right;
} Instruction;
void Logical_MOV(ARM_WORD reg_d, ARM_WORD op2);

void Logical_MVN(ARM_WORD reg_d, ARM_WORD op2);

/**
 * Arithmetic Instructions
 */
 //TODO VERY IMPORTANT, THESE INSTRUCTIONS NEED TO UPDATE NZCV FLAGS!!
void Arithmetic_ADD(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);

void Arithmetic_ADDC(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);

void Arithmetic_SUB(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2);

void Arithmetic_CMP(ARM_WORD reg_d, ARM_WORD op2, bool immediate);


/**
 * Update the condition flags from the given ARM_WORD (uint32_t)
 */
void update_condition_flags(ARM_WORD flags);
#endif //DONGBOYADVANCE_INSTRUCTION_SET_H
