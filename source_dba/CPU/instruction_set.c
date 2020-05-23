//
// Created by johnm on 5/12/2020.
//

#include "instruction_set.h"

/**
 * Currently should work with ADD, SUB
 */
void update_condition_flags(ARM_U_WORD flags) {
    cpsr.status |= flags;
}

void Logical_MOV(ARM_U_WORD reg_d, ARM_U_WORD op2) {
    gpr.registers[reg_d].data = op2;
    if (debug) {
        print_gen_reg();
    }

}

void Arithmetic_ADD(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD op2) {
    if (reg_d == reg_n) {
        gpr.registers[reg_d].data += op2;
    } else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data + op2;
    }
}

void Arithmetic_SUB(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD op2) {
    if (reg_d == reg_n) {
        gpr.registers[reg_d].data -= op2;
    } else {
        gpr.registers[reg_d].data = gpr.registers[reg_n].data - op2;
    }
}

/**
 * reg_d - op2, set corresponding arithmetic flag
 * @todo Verifiy CMP works correctly
 * @body Same as title, @Critical
 */
void Arithmetic_CMP(ARM_U_WORD reg_d, ARM_U_WORD op2, bool immediate) {
    ARM_U_WORD cmp_result;
    ARM_U_WORD left = gpr.registers[reg_d].data;
    ARM_U_WORD right;
    if (immediate) {
        right = op2;;
    } else {
        right = gpr.registers[op2].data;
    }
    ARM_U_WORD flags = 0x0;
    //TODO define signed versions of ARM word
    int32_t SIGNED_WORD = (int32_t) left - (int32_t) right;
    ARM_U_WORD UNSIGNED_WORD = left - right;
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
    if ((signed_left > 0 && signed_right < 0 && SIGNED_WORD <= signed_right) ||
        (signed_left < 0 && signed_right > 0 && SIGNED_WORD >= signed_left)) {
        flags |= 1 << 28;
    }
    update_condition_flags(flags);
}


void Arithmetic_AND_Immediate(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD immediate) {
    if (dest == reg_d) {
        gpr.registers[dest].data &= immediate;
    } else {
        gpr.registers[dest].data = gpr.registers[reg_d].data & immediate;
    }
}

/**
 * @todo Add carry flag update to this instruction
 * @body Not exactly sure, but the instruction should at least set the CPSR.Carry to whatever the current carry flag is. Labels: @Improvement
 */
void Arithmetic_ANDS_Immediate(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD immediate) {
    /**
     * Normal AND part
     */
    ARM_U_WORD result = gpr.registers[reg_d].data & immediate;
    gpr.registers[dest].data = result;
    /**
     * S part, set flags
     */
    cpsr.N_Sign_flag = result >> 31;
    cpsr.Z_Zero_flag = result == 0;
    cpsr.C_Carry_flag = cpsr.C_Carry_flag;
}

void Arithmetic_AND_Register(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n) {
    gpr.registers[dest].data = gpr.registers[reg_d].data & gpr.registers[reg_n].data;
}

void Arithmetic_ANDS_Register(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n) {
    ARM_U_WORD result = gpr.registers[reg_d].data & gpr.registers[reg_n].data;
    /**
     * S part, set flags
     */
    cpsr.N_Sign_flag = result >> 31;
    cpsr.Z_Zero_flag = result == 0;
    cpsr.C_Carry_flag = cpsr.C_Carry_flag;
}


//2nd operand is register-shifted register
void Arithmetic_AND_Register_Shifted(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD reg_n_offset) {
    ARM_U_WORD offset = sizeof(ARM_U_WORD) * reg_n_offset;
    ARM_U_WORD array_start = gpr.registers[reg_n].data;
    ARM_U_WORD element_address = array_start+offset;
    ARM_U_WORD element = get_word(element_address);
    ARM_U_WORD result = gpr.registers[reg_d].data & element;

    gpr.registers[dest].data=result;
}

void Arithmetic_ANDS_Register_Shifted(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD reg_n_offset) {
    ARM_U_WORD result = gpr.registers[reg_d].data & gpr.registers[reg_n].data + sizeof(ARM_U_WORD) * reg_n_offset;

    gpr.registers[dest].data=result;
    /**
     * S part, set flags
     */
    cpsr.N_Sign_flag = result >> 31;
    cpsr.Z_Zero_flag = result == 0;
    cpsr.C_Carry_flag = cpsr.C_Carry_flag;
}
bool check_condition(Branch_Condition condition) {
    switch (condition) {
        case EQ:
            return cond_flags.EQ;
        case NE:
            break;
        case CS:
            break;
        case HS:
            break;
        case CC:
            break;
        case LO:
            break;
        case MI:
            break;
        case PL:
            break;
        case VS:
            break;
        case VC:
            break;
        case HI:
            break;
        case LS:
            break;
        case GE:
            break;
        case LT:
            break;
        case GT:
            break;
        case LE:
            break;
        case AL:
            break;
    }
}

void Jump_Branch(ARM_U_WORD cond, ARM_U_WORD label) {
    General_Message msg;
    //sprintf(msg.instruction_name,"JUMP BRANCH | COND->%s | LABEL->[%0x8x]",);
    ARM_S_WORD branch_addr = label - pc.r15.data;

    if(check_condition(cond)) {
        pc.r15.data = (ARM_U_WORD) branch_addr;
        //msg.
    }
    /**
     * TODO add failed branch condition message
     */
    else {

    }
    log_msg(msg);
}
