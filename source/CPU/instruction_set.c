//
// Created by johnm on 5/12/2020.
//

#include "instruction_set.h"
/**
 * Currently should work with ADD, SUB
 */
void update_condition_flags(ARM_WORD flags) {
    cpsr.status |= flags;
}
void Logical_MOV(ARM_WORD reg_d, ARM_WORD op2) {
    gpr.registers[reg_d].data = op2;
    if(debug) {
        print_gen_reg();
    }

}
void Arithmetic_ADD(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2) {
    if(reg_d==reg_n) {
        gpr.registers[reg_d].data += op2;
    }
    else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data + op2;
    }
}

void Arithmetic_SUB(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2) {
    if(reg_d==reg_n) {
        gpr.registers[reg_d].data -= op2;
    }
    else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data - op2;
    }
}
/**
 * reg_d - op2, set corresponding arithmetic flag
 */
void Arithmetic_CMP(ARM_WORD reg_d, ARM_WORD op2, bool immediate) {
    ARM_WORD cmp_result;
    if(immediate) {
        cmp_result= gpr.registers[reg_d].data - op2;
    }
    else {
        cmp_result= gpr.registers[reg_d].data - gpr.registers[op2].data;
    }
    ARM_WORD flags=0x0;
    if(cmp_result==0 ) {
        flags |= 1 << 30;
    }
    update_condition_flags(flags);
}

