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
    if (debug) {
        print_gen_reg();
    }

}

void Arithmetic_ADD(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2) {
    if (reg_d == reg_n) {
        gpr.registers[reg_d].data += op2;
    } else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data + op2;
    }
}

void Arithmetic_SUB(ARM_WORD reg_d, ARM_WORD reg_n, ARM_WORD op2) {
    if (reg_d == reg_n) {
        gpr.registers[reg_d].data -= op2;
    } else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data - op2;
    }
}

/**
 * reg_d - op2, set corresponding arithmetic flag
 */
void Arithmetic_CMP(ARM_WORD reg_d, ARM_WORD op2, bool immediate) {
    ARM_WORD cmp_result;
    ARM_WORD left = gpr.registers[reg_d].data;
    ARM_WORD right;
    if (immediate) {
        right = op2;;
    } else {
        right = gpr.registers[op2].data;
    }
    ARM_WORD flags = 0x0;
    //TODO define signed versions of ARM word
    int32_t SIGNED_WORD = (int32_t) left - (int32_t) right;
    ARM_WORD UNSIGNED_WORD = left - right;
    /**
     * Check if equal, have to evaluate both signed and unsigned cases
     */
    if (SIGNED_WORD == 0 && UNSIGNED_WORD == 0) {
        flags |= 1 << 30;
    }
    /**
     * Check for sign flag, have to check that signed - signed < 0 AND signed - unsigned
     */
    if (SIGNED_WORD < 0) {
        flags |= 1 << 31;
    }
    /**
     * If a -b > (a || b), set carry flag
     */
    if (UNSIGNED_WORD > left && UNSIGNED_WORD > right) {
        flags |= 1 << 29;
    }
    //TODO cleanup
    /**
     * Check if a signed positive - signed negative  < signed negative
     */
    int32_t signed_left = (int32_t) left;
    int32_t signed_right = (int32_t) right;
    /*
     *      a > 0, b < 0, a - b < b      (|a| + |b|) < -b                                           a < 0, b > 0, a - b < a (-a - b) > b
     */
    if ( (signed_left > 0 && signed_right < 0 && SIGNED_WORD <= signed_right) || (signed_left < 0 && signed_right > 0 && SIGNED_WORD >= signed_left)) {
        flags |= 1 << 28;
    }
    update_condition_flags(flags);
}

