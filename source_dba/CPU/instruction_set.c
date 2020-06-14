//
// Created by johnm on 5/12/2020.
//

#include "instruction_set.h"

void print_binary(ARM_U_WORD opcode) {
    for (ARM_U_WORD i = 1 << 31; i > 0; i = i / 2) {
        (opcode & i) ? printf("1  ") : printf("0  ");
    }
    printf("\n");
    for (ARM_S_WORD i = 31; i >= 0; i--) {
        if (i < 10) {
            printf("%d  ", i);
        } else {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void print_binary_THUMB(ARM_U_WORD opcode) {
    for (ARM_U_WORD i = 1 << 15; i > 0; i = i / 2) {
        (opcode & i) ? printf("1  ") : printf("0  ");
    }
    printf("\n");
    for (ARM_S_WORD i = 15; i >= 0; i--) {
        if (i < 10) {
            printf("%d  ", i);
        } else {
            printf("%d ", i);
        }
    }
    printf("\n");
}

char *ALU_as_string(ALU_Opcode_Alias instr) {
    char *alu_string = (char *) malloc(sizeof(ARM_U_BYTE) * 4);
    switch (instr) {

        case AND:
            strncpy(alu_string, "AND\0", 4);
            break;
        case XOR:
            strncpy(alu_string, "XOR\0", 4);
            break;
        case SUB:
            strncpy(alu_string, "SUB\0", 4);
            break;
        case RSB:
            strncpy(alu_string, "RSB\0", 4);
            break;
        case ADD:
            strncpy(alu_string, "ADD\0", 4);
            break;
        case ADC:
            strncpy(alu_string, "ADC\0", 4);
            break;
        case SBC:
            strncpy(alu_string, "SBC\0", 4);
            break;
        case RSC:
            strncpy(alu_string, "RSC\0", 4);
            break;
        case TST:
            strncpy(alu_string, "TST\0", 4);
            break;
        case TEQ:
            strncpy(alu_string, "TEQ\0", 4);
            break;
        case CMP:
            strncpy(alu_string, "CMP\0", 4);
            break;
        case CMN:
            strncpy(alu_string, "CMN\0", 4);
            break;
        case ORR:
            strncpy(alu_string, "ORR\0", 4);
            break;
        case MOV:
            strncpy(alu_string, "MOV\0", 4);
            break;
        case BIC:
            strncpy(alu_string, "BIC\0", 4);
            break;
        case MVN:
            strncpy(alu_string, "MVN\0", 4);
            break;
    }
    return alu_string;
}

char *shift_as_string(Shift_Type shift) {
    char *shift_string = (char *) malloc(sizeof(ARM_U_BYTE) * 12);
    switch (shift) {

        case LSL:
            strncpy(shift_string, "LSL\0", 12);
            break;
        case LSR:
            strncpy(shift_string, "LSR\0", 12);
            break;
        case ASR:
            strncpy(shift_string, "ASR\0", 12);
            break;
        case ROR:
            strncpy(shift_string, "ROR\0", 12);
            break;
    }
    return shift_string;
}

char *condition_as_string(Condition_Alias cond) {
    char *cond_string = (char *) malloc(sizeof(ARM_U_BYTE) * 3);
    switch (cond) {

        case EQ:
            strncpy(cond_string, "EQ\0", 3);
            break;
        case NE:
            strncpy(cond_string, "NE\0", 3);
            break;
        case CS:
            strncpy(cond_string, "CS\0", 3);
            break;
        case CC:
            strncpy(cond_string, "CC\0", 3);
            break;
        case MI:
            strncpy(cond_string, "MI\0", 3);
            break;
        case PL:
            strncpy(cond_string, "PL\0", 3);
            break;
        case VS:
            strncpy(cond_string, "VS\0", 3);
            break;
        case VC:
            strncpy(cond_string, "VC\0", 3);
            break;
        case HI:
            strncpy(cond_string, "HI\0", 3);
            break;
        case LS:
            strncpy(cond_string, "LS\0", 3);
            break;
        case GE:
            strncpy(cond_string, "GE\0", 3);
            break;
        case LT:
            strncpy(cond_string, "LT\0", 3);
            break;
        case GT:
            strncpy(cond_string, "GT\0", 3);
            break;
        case LE:
            strncpy(cond_string, "LE\0", 3);
            break;
        case AL:
            strncpy(cond_string, "AL\0", 3);
            break;
    }
    return cond_string;
}

/**
 * Currently should work with ADD, SUB
 */
void update_condition_flags(ARM_U_WORD flags) {
    cpsr.status |= flags;
}

/**
 * ALU IMMEDIATE INSTRUCTIONS
 */

void Arithmetic_AND_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD immediate) {
    ARM_U_WORD result = reg_n_data & immediate;
    set_reg(reg_d, result);

}

void Arithmetic_EOR_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD immediate) {
    ARM_U_WORD result = reg_n_data ^immediate;
    set_reg(reg_d, result);

}

void Arithmetic_SUB_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data - Op2;
    set_reg(reg_d, result);

}

void Arithmetic_RSB_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = Op2 - reg_n_data;
    set_reg(reg_d, result);

}

void Arithmetic_ADD_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data + Op2;
    set_reg(reg_d, result);
    //gpr.registers[reg_d].data = gpr.registers[reg_n].data + Op2;
}

void Arithmetic_ADC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data + Op2 + cpsr.C_Carry_flag;
    set_reg(reg_d, result);

}

void Arithmetic_SBC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data - Op2 + cpsr.C_Carry_flag - 1;
    set_reg(reg_d, result);

}

void Arithmetic_RSC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = Op2 - reg_n_data + cpsr.C_Carry_flag - 1;
    set_reg(reg_d, result);
}

void Arithmetic_TST_Immediate(ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    ARM_U_WORD result = gpr.registers[reg_n].data & Op2;
}

void Arithmetic_TEQ_Immediate(ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    ARM_U_WORD result = gpr.registers[reg_n].data ^Op2;
}

void Arithmetic_CMP_Immediate(ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    ARM_U_WORD result = gpr.registers[reg_n].data - Op2;
}

void Arithmetic_CMN_Immediate(ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    ARM_U_WORD result = gpr.registers[reg_n].data + Op2;
}

void Arithmetic_ORR_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data | Op2;
    set_reg(reg_d, result);
}

void Arithmetic_MOV_Immediate(ARM_U_WORD reg_d, ARM_U_WORD Op2) {
    set_reg(reg_d, Op2);
}

void Arithmetic_BIC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n_data, ARM_U_WORD Op2) {
    ARM_U_WORD result = reg_n_data & ~(Op2);
    set_reg(reg_d, result);
}

void Arithmetic_MVN_Immediate(ARM_U_WORD reg_d, ARM_U_WORD Op2) {
    ARM_U_WORD result = ~(Op2);
    set_reg(reg_d, result);
}

/**
 * ALU IMMEDIATE UTILITY INSTRUCTIONS
 */
ARM_U_WORD LSL_Imm(ARM_U_WORD immediate, ARM_U_WORD shift_amount) {
    ARM_U_WORD result = immediate << shift_amount;
    return result;
}

ARM_U_WORD LSR_Imm(ARM_U_WORD immediate, ARM_U_WORD shift_amount) {
    ARM_U_WORD result = immediate >> shift_amount;
    return result;
}

ARM_U_WORD ASR_Imm(ARM_U_WORD immediate, ARM_U_WORD shift_amount) {
    ARM_U_WORD sign_bit = immediate & BIT31;
    for (ARM_U_WORD i = shift_amount; i > 0; i--) {
        immediate >>= 1;
        immediate |= (sign_bit);
    }
    return immediate;
}

ARM_U_WORD ROR_RRX_Imm(ARM_U_WORD immediate) {
    return immediate;
}

ARM_U_WORD ROR_Imm(ARM_U_WORD immediate, ARM_U_WORD shift_amount) {
    ARM_U_WORD operand = immediate;
    if (shift_amount == 0) {
        return ROR_RRX_Imm(immediate);
    }
    ARM_U_WORD operand_mask = (1 << shift_amount) - 1;
    ARM_U_WORD leftover_mask = operand_mask ^0xffffffff;
    ARM_U_WORD result = (operand & operand_mask) << ((sizeof(ARM_U_WORD) * 8) - shift_amount);
    printf("Performed ROR shift on immediate: imm=[0x%08x] operand_mask=[0x%08x] leftover_mask=[0x%08x] result=[0x%08x]\n",
           immediate, operand_mask, leftover_mask, result);
    return result;
}

Shift_Type get_shift_alias(ARM_U_WORD shift_type) {
    switch (shift_type) {
        case 0x0:
            return LSL;
        case 0x1:
            return LSR;
        case 0x2:
            return ASR;
        case 0x3:
            return ROR;
    }
}

ARM_U_WORD Shift(ARM_U_WORD immediate, ARM_U_WORD shift_amount, Shift_Type shift_type) {
    switch (shift_type) {

        case LSL:
            return LSL_Imm(immediate, shift_amount);
        case LSR:
            return LSR_Imm(immediate, shift_amount);
        case ASR:
            return ASR_Imm(immediate, shift_amount);
        case ROR:
            return ROR_Imm(immediate, shift_amount);
    }
}

/**
 * ALU IMMEDIATE INSTRUCTIONS END
 */





/**
 * reg_d - op2, set corresponding arithmetic flag
 * @todo Verifiy CMP works correctly
 * @body Same as title, @Critical
 */
void Arithmetic_CMP(ARM_U_WORD reg_n, ARM_U_WORD op2, bool immediate) {
    ARM_U_WORD cmp_result;
    ARM_U_WORD left = gpr.registers[reg_n].data;
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
    ARM_U_WORD element_address = array_start + offset;
    ARM_U_WORD element = get_word(element_address);
    ARM_U_WORD result = gpr.registers[reg_d].data & element;

    gpr.registers[dest].data = result;
}

void Arithmetic_ANDS_Register_Shifted(ARM_U_WORD dest, ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD reg_n_offset) {
    ARM_U_WORD result = gpr.registers[reg_d].data & gpr.registers[reg_n].data + sizeof(ARM_U_WORD) * reg_n_offset;

    gpr.registers[dest].data = result;
    /**
     * S part, set flags
     */
    cpsr.N_Sign_flag = result >> 31;
    cpsr.Z_Zero_flag = result == 0;
    cpsr.C_Carry_flag = cpsr.C_Carry_flag;
}

void push_reg(ARM_U_WORD reg) {
    ARM_U_WORD address = sp.r13.data;
    ARM_U_WORD reg_data = get_reg_data(reg);
    write_memory(address, reg_data, WORD);
    set_reg(13, sp.r13.data - 4);
}

void pop(void);

bool check_condition(Branch_Condition condition) {
    switch (condition) {
        case EQ:
            return cpsr.Z_Zero_flag;
        case NE:
            return !cpsr.Z_Zero_flag;
        case CS:
            return cpsr.C_Carry_flag;
        case CC:
            return !cpsr.C_Carry_flag;
        case MI:
            return cpsr.N_Sign_flag;
        case PL:
            return !cpsr.N_Sign_flag;
        case VS:
            return cpsr.V_Overflow_flag;
        case VC:
            return !cpsr.V_Overflow_flag;
        case HI:
            return cpsr.C_Carry_flag && cpsr.Z_Zero_flag;
        case LS:
            return !cpsr.C_Carry_flag || cpsr.Z_Zero_flag;
        case GE:
            return cpsr.N_Sign_flag == cpsr.V_Overflow_flag;
        case LT:
            return cpsr.N_Sign_flag != cpsr.V_Overflow_flag;
        case GT:
            return !cpsr.Z_Zero_flag && (cpsr.N_Sign_flag == cpsr.V_Overflow_flag);
        case LE:
            return cpsr.Z_Zero_flag || cpsr.N_Sign_flag != cpsr.V_Overflow_flag;
        case AL:
            return true;
    }
}

void Jump_Branch(ARM_U_WORD cond, ARM_U_WORD label) {
    General_Message msg;
    //sprintf(msg.instruction_name,"JUMP BRANCH | COND->%s | LABEL->[%0x8x]",);
    ARM_S_WORD branch_addr = label - pc.r15.data;

    if (check_condition(cond)) {
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

/**
 * @todo Implement software interrupt opcode
 * @body Implement SWI for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void software_interrupt(ARM_U_WORD opcode) {
    printf("SWI occurs here @ [0x%0x]\n", opcode);
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    ARM_U_WORD instruction = (opcode & (BIT27 | BIT26 | BIT25 | BIT24)) >> 24;
    //Software interrupt
    if (instruction == 0xf) {
        /**
         * @todo Implement software interrupt routine in the SWI/BKPT opcode
         * @body The @Opcode has a specific routine for software interrupts that can be seen in GBATEK.
         */
    }
        //Breakpoint
    else if (instruction == 0x1) {
        debug_assert(condition == 0xe,
                     "condition is not 0xe when opcode should be condition=0xe");
        ARM_U_WORD bkpt_check_1 = (opcode & (BIT23 | BIT22 | BIT21 | BIT20)) >> 20;
        debug_assert(bkpt_check_1 == 0x2, "bkpt_check_1 is not 0x2 when opcode should be bkpt_check_1=0x2");
        ARM_U_WORD bkpt_check_2 = (opcode & (BIT7 | BIT6 | BIT5 | BIT4));
        debug_assert(bkpt_check_2 == 0x7, "bkpt_check_2 is not 0x7 when opcode should be bkpt_check_2=0x7");
    }
}

/**
 * @todo Implement Co-register transfer
 * @body Implement CoRegTrans for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void CoRegTrans(ARM_U_WORD opcode) {
    printf("Coprocessor register operation occurs here\n");
}

/**
 * @todo Implement Co-data operation opcode
 * @body Implement CoDataOp for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void CoDataOp(ARM_U_WORD opcode) {
    printf("Coprocessor data operation occurs here\n");
}

/**
 * @todo Implement Co-Data transfer opcode
 * @body Implement CoDataTrans for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void CoDataTrans(ARM_U_WORD opcode) {
    printf("CoDataTrans occurs here\n");
}

/**
 * @todo Implement Branch opcode
 * @body Implement Branch for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void Branch(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);

    ARM_U_WORD check = (opcode & (BIT27 | BIT26 | BIT25)) >> 25;

    debug_assert(check == 0x5, "Check must be 0x5 for this instruction");
    ARM_U_WORD branch_type = (opcode & (BIT24)) >> 24;

    ARM_S_WORD nn = (opcode & ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 | BIT25 | BIT24));
    ARM_U_WORD address = pc.r15.data + 8 + (nn * 4);
    char branch_string[128];

#ifdef _BUILD_WITH_LOGGING
    if (log_level & LOG_INSTRUCTION) {

        printf("0x%08x: 0x%08x\t%s %s 0x%08x\n", pc.r15.data, opcode, branch_type ? "B" : "BL",
               condition_as_string(condition_alias), address);
    }
    if (log_level & LOG_OPCODE) {
        if (branch_type) {
            sprintf(branch_string, "Branch with Link; PC: 0x%08x -> 0x%08x, LR: 0x%08x", pc.r15.data, address,
                    pc.r15.data + 4);
        } else {
            sprintf(branch_string, "Branch; PC: 0x%08x -> 0x%08x", pc.r15.data, address);
        }
        printf("Opcode: [Branch|0x%08x\nBinary format:\n", opcode);
        print_binary(opcode);
        printf("Condition: 0x%x\n"
               "Check: 0x%x\n"
               "%s\n",
               condition,
               check,
               branch_string);
    }
#endif
    bool pass_condition = check_condition(condition_alias);
    if (pass_condition) {
        switch (branch_type) {
            case 0x0:
                set_pc(address);
                break;
            case 0x1:
                set_lr(pc.r15.data + 4);
                set_pc(address);
                break;
        }
    }
}

/**
 * @todo Implement Branch Exchange opcode
 * @body Implement BranchExchange for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void BranchExchange(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);

    ARM_U_WORD check_1 = (opcode & (0x12fff << 8)) >> 8;
    debug_assert(check_1 == 0x12fff, "Bits [27,8] must be 0x12fff");
    ARM_U_WORD operation = (opcode & (BIT7 | BIT6 | BIT5 | BIT4)) >> 4;

    ARM_U_WORD reg_n = (opcode & (BIT3 | BIT2 | BIT1 | BIT0));
    ARM_U_WORD reg_n_data = get_reg_data(reg_n);

    bool switch_operating_mode = reg_n_data & BIT0;
    cpsr.T_state_bit = switch_operating_mode;

#ifdef  _BUILD_WITH_LOGGING
    if (log_level & LOG_INSTRUCTION) {
        printf("0x%08x: 0x%08x BX %s\n", get_reg_data(15), opcode, register_as_string(reg_n));
        printf("operating mode set to %s\n", switch_operating_mode ? "T" : "A32");
    }
#endif
    if (cpsr.T_state_bit) {
        ARM_U_WORD new_addr = reg_n_data & 0xFFFFFFFE;
        set_pc(new_addr);
    }

}

/**
 * @todo Implement Transfer Swap12 transfer opcode
 * @body Implement TransSwp12 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransSwp12(ARM_U_WORD opcode) {
    printf("TransSwp12 occurs here\n");
}

/**
 * @todo Implement Transfer Register 10 opcode
 * @body Implement TransReg10 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransReg10(ARM_U_WORD opcode) {
    printf("TransReg10 occurs here\n");
}

/**
 * @todo Implement Transfer Immediate 10 opcode
 * @body Implement TransImm10 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransImm10(ARM_U_WORD opcode) {
    printf("TransImm10 occurs here\n");
}

/**
 * @todo Implement Transfer Register 9 opcode
 * @body Implement TransReg9 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransReg9(ARM_U_WORD opcode) {
    printf("TransReg9 occurs here\n");
}

/**
 * @todo Implement Transfer Immediate 9 opcode
 * @body Implement TransImm9 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransImm9(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);

    ARM_U_WORD check = (opcode & (BIT27 | BIT26)) >> 26;
    debug_assert(check == 0x1, "Check must be 0x1 for this instruction");

    bool Immediate_Offset_Flag = (opcode & (BIT25)) >> 25; //0=Immediate, 1=Shifted Register
    debug_assert(Immediate_Offset_Flag == 0, "Immediate_Offset_Flag must be false for this instruction");

    bool P = (opcode & (BIT24)) >> 24; //0=post; add offset after transfer, 1=pre; before trans.
    bool U = (opcode & (BIT23)) >> 23;
    bool B = (opcode & (BIT22)) >> 22;
    bool Memory_Management = (opcode & (BIT21)) >> 21;
    bool Write_Back = (opcode & (BIT21)) >> 21;
    bool L = (opcode & (BIT20)) >> 20;
    ARM_U_WORD reg_n = (opcode & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16; //Base register
    ARM_U_WORD reg_d = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12; //Source/Destination Register
    ARM_U_WORD reg_n_data = get_reg_data(reg_n);
    if (reg_n == 15) {
        reg_n_data += 8;
    }
    ARM_U_WORD reg_d_data = get_reg_data(reg_d);
    if (reg_d == 15) {
        reg_d_data += 12;
    }
    ARM_U_WORD Offset = (opcode &
                         (BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0));
    if (log_level & LOG_OPCODE) {
        char Bit_21_String[128];
        if (P) {
            sprintf(Bit_21_String, "W: %s;write-back is OPTIONAL",
                    Write_Back ? "write address into base" : "no write-back");
        } else {
            sprintf(Bit_21_String, "T: %s;write-back is ALWAYS enabled",
                    Memory_Management ? "1=Force non-privileged access" : "0=Normal");
        }
        printf("Opcode: [TransImm9|0x%08x]\nBinary Format:\n", opcode);
        print_binary(opcode);
        printf("Condition: 0x%x\n"
               "Check: 0x%x\n"
               "I(Immediate Offset Flag): %s\n"
               "P: %s\n"
               "U: %s\n"
               "B: %s\n"
               "%s\n"
               "L: %s\n"
               "reg_n: %d reg_n.data=[0x%08x]\n"
               "reg_d: %d reg_d.data=[0x%08x]\n"
               "Offset: 0x%08x\n",
               condition,
               check,
               Immediate_Offset_Flag ? "1=Shifted_Register" : "0=Immediate",
               P ? "1=pre;add offset before transfer" : "0=post;add offset after transfer",
               U ? "1=up;add offset to base" : "0=down;subtract offset from base",
               B ? "1=transfer 8bit/byte" : "0=transfer 32bit/word",
               Bit_21_String,
               L ? "1=LDR -> Load from memory" : "0=STR -> Store to memory",
               reg_n, reg_n_data, reg_d,
               reg_d_data, Offset);
    }
    bool pass_condition = check_condition(condition_alias);
    Alignment alignment = B ? BYTE : WORD;
    ARM_U_WORD offset_addr;
    ARM_U_WORD address;
    ARM_U_WORD data;
    if (pass_condition) {
        /**
         * Up/Down check
         */
        if (U) {
            offset_addr = reg_n_data + Offset;
        } else {
            offset_addr = reg_n_data - Offset;
        }
        /**
         * Index check
         */
        if (P) {
            address = offset_addr;
        } else {
            address = reg_n_data;
        }
        if (log_level & LOG_INSTRUCTION) {
            printf("0x%08x: 0x%08x %s %s %s,[0x%08x]\n", get_reg_data(reg_n), opcode, L ? "LDR" : "STR",
                   condition_as_string(condition_alias), register_as_string(reg_d), address);
        }
        switch ((ARM_U_BYTE) L) {
            case 0x0:

                write_memory(address, reg_d_data, alignment);

                break;
            case 0x1:
                data = read_memory(address, alignment);
                set_reg(reg_d, data);
                break;
            default:
                break;
        }
        if (Write_Back) {
            data = offset_addr;
            set_reg(reg_n, data);
        }
    }
    set_pc(get_reg_data(15) + 4);
}

/**
 * @todo Implement Block Transfer opcode
 * @body Implement BlockTrans for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void BlockTrans(ARM_U_WORD opcode) {
    printf("BlockTrans occurs here\n");
}

/**
 * @todo Implement Multiply Long opcode
 * @body Implement MulLong for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void MulLong(ARM_U_WORD opcode) {
    printf("MulLong occurs here\n");
}

/**
 * @todo Implement Multiply opcode
 * @body Implement Multiply for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void Multiply(ARM_U_WORD opcode) {
    printf("Multiply occurs here\n");
}

/**
 * @todo Implement PSR Register opcode
 * @body Implement PSR Reg for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void PSR_Reg(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);

    ARM_U_WORD check = (opcode & (BIT27 | BIT26)) >> 26;

    debug_assert(check == 0x0, "Check must be 0x0 for this instruction");
    bool I = (opcode & (BIT25)) >> 25;
    ARM_U_WORD check_2 = (opcode & (BIT24 | BIT23)) >> 23;

    debug_assert(check_2 == 0x2, "Check_2 must be 0x2 for this instruction");

    bool register_mode = (opcode & (BIT22)) >> 22;
    bool OP = (opcode & (BIT21)) >> 21;

    bool check_3 = (opcode & (BIT20)) >> 20;
    debug_assert(check_3 == 0x0, "Check_3 must be 0x0 for this instruction");

    ARM_U_WORD reg_d, check_4;
    bool f = false, s = false, x = false, c = false;
    /**
     *  Opcode
           0: MRS{cond} Rd,Psr          ;Rd = Psr
           1: MSR{cond} Psr{_field},Op  ;Psr[field] = Op
     */
    /**
     * @todo Add saved(banked) registers so that MSR/MRS instructions can function properly. @Critical, @Opcode
     */
    bool passed_condition = check_condition(condition_alias);
    if (passed_condition) {
        if (OP) {
            /**
             * MSR {cond} Psr{_field},Op; Psr[field] = Op
             */
            f = (opcode & (BIT19)) >> 19;
            s = (opcode & (BIT18)) >> 18;
            x = (opcode & (BIT17)) >> 17;
            c = (opcode & (BIT16)) >> 16;
            check_4 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12;
            debug_assert(check_4 == 0xf, "Check_4 must be 0xf for this instruction");
            /**
             * If immediate
             */
            if (I) {
                ARM_U_WORD shift = (opcode & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8;
                ARM_U_WORD imm = (opcode & (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0));
                ARM_U_WORD nn = ROR_Imm(imm, shift);

            } else {
                ARM_U_WORD reg_m = (opcode & (0xf)) >> 4;
                ARM_U_WORD reg_m_data = get_reg_data(reg_m);


                ARM_U_WORD check_5 = (opcode & (BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4)) >> 4;
                debug_assert(check_5 == false, "Check_5 must be 0x0 for this instruction, else it is a BX instruction");
                if (log_level & LOG_INSTRUCTION) {

                    printf("0x%08x: 0x%08x\tMSR %s _%s%s, %s\n",
                           pc.r15.data,
                           opcode,
                           register_mode ? spsr_as_string() : "cpsr",
                           f ? "f" : "_",
                           c ? "c" : "_",
                           register_as_string(reg_m));
                }
                ARM_U_WORD retval = get_current_SPSR(&cpsr);
                if (retval == 0) {
                    ARM_U_WORD mask = 0;
                    if (f) {
                        mask |= (BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 | BIT25 | BIT24);
                    }
                    if (c) {
                        mask |= (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
                    }
                    //reg_m_data
                    cpsr.status = mask & reg_m_data;
                }
            }
        } else {
            check_4 = (opcode & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16;
            debug_assert(check_4 == 0xf, "Check_4 must be 0xf for this instruction");
            reg_d = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12;

        }
    }
    set_pc(pc.r15.data + 4);

}

/**
 * @todo Implement PSR Immediate opcode
 * @body Implement PSR Imm for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void PSR_Imm(ARM_U_WORD opcode) {
    printf("PSR_Imm occurs here\n");

}

void THUMB_move_shifted_register(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13)) >> 13;
    debug_assert(check_1 == 0x0, "check_1 must be 0x0 for this instruciton");

    ARM_U_WORD shift_type = (opcode & (BIT12 | BIT11)) >> 11;
    Shift_Type shift_alias = get_shift_alias(shift_type);
    ARM_U_WORD offset = (opcode & (BIT10 | BIT9 | BIT8 | BIT7 | BIT6)) >> 6;
    ARM_U_WORD reg_s = (opcode & (BIT5 | BIT4 | BIT3)) >> 3;
    ARM_U_WORD reg_s_data = get_reg_data(reg_s);
    ARM_U_WORD reg_d = (opcode & (BIT2 | BIT1 | BIT0));
    ARM_U_WORD reg_d_data = get_reg_data(reg_d);
    if (log_level & LOG_INSTRUCTION) {
        printf("0x%08x: 0x%08x  %s %s,%s, #%d\n",
               get_reg_data(15),
               opcode,
               shift_as_string(shift_alias),
               register_as_string(reg_d),
               register_as_string(reg_s),
               offset);
    }
    ARM_U_WORD shifted_offset = Shift(reg_s_data, offset, shift_alias);
    Arithmetic_MOV_Immediate(reg_d, shifted_offset);
    set_reg(15, get_reg_data(15) + 2);
}

void THUMB_add(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11;
    debug_assert(check_1 == 0x3, "check_1 must be 0x3 for this instruction");
    ARM_U_WORD op = (opcode & (BIT10 | BIT9)) >> 9;

    ARM_U_WORD result = 0;
    ARM_U_WORD operand = (opcode & (BIT8 | BIT7 | BIT6)) >> 6;
    ARM_U_WORD reg_s = (opcode & (BIT5 | BIT4 | BIT3)) >> 3;
    ARM_U_WORD reg_s_data = get_reg_data((reg_s));
    ARM_U_WORD reg_d = (opcode & (BIT2 | BIT1 | BIT0));

    /**
    * ADD {S} register
    */
    if (op == 0x0) {
        if (log_level & LOG_INSTRUCTION) {
            printf("0x%08x: 0x%08x  %s %s,%s,%s",
                   get_reg_data(15),
                   opcode,
                   ALU_as_string(ADD),
                   register_as_string(reg_d),
                   register_as_string(reg_s),
                   register_as_string(operand));
        }
        result = reg_s_data + get_reg_data(operand);
        set_reg(reg_d, result);
    }
        /**
        * ADD {S} immediate
        */
    else if (op == 0x2) {
        if (log_level & LOG_INSTRUCTION) {
            printf("0x%08x: 0x%08x  %s %s,%s,#%d",
                   get_reg_data(15),
                   opcode,
                   ALU_as_string(ADD),
                   register_as_string(reg_d),
                   register_as_string(reg_s),
                   operand);
        }
        result = reg_s_data + operand;
        set_reg(reg_d, result);
    }
}

void THUMB_subtract(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11;
    debug_assert(check_1 == 0x3, "check_1 must be 0x3 for this instruction");
    ARM_U_WORD op = (opcode & (BIT10 | BIT9)) >> 9;

    ARM_U_WORD result = 0;
    ARM_U_WORD operand = (opcode & (BIT8 | BIT7 | BIT6)) >> 6;
    ARM_U_WORD reg_s = (opcode & (BIT5 | BIT4 | BIT3)) >> 3;
    ARM_U_WORD reg_s_data = get_reg_data((reg_s));
    ARM_U_WORD reg_d = (opcode & (BIT2 | BIT1 | BIT0));
    /**
    * SUB {S} register
    */
    if (op == 0x0) {
        if (log_level & LOG_INSTRUCTION) {
            printf("0x%08x: 0x%08x  %s %s,%s,%s",
                   get_reg_data(15),
                   opcode,
                   ALU_as_string(SUB),
                   register_as_string(reg_d),
                   register_as_string(reg_s),
                   register_as_string(operand));
        }
        result = reg_s_data - get_reg_data(operand);
        set_reg(reg_d, result);
    }
        /**
        * SUB {S} immediate
        */
    else if (op == 0x2) {
        if (log_level & LOG_INSTRUCTION) {
            printf("0x%08x: 0x%08x  %s %s,%s,#%d",
                   get_reg_data(15),
                   opcode,
                   ALU_as_string(SUB),
                   register_as_string(reg_d),
                   register_as_string(reg_s),
                   operand);
        }
        result = reg_s_data - operand;
        set_reg(reg_d, result);
    }
}

void THUMB_move(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13)) >> 13;
    debug_assert(check_1 == 0x1, "check_1 must be 0x1 for this instruction");

    ARM_U_WORD reg_d = (opcode & (BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD nn = (opcode & (0xff));
    if (log_level & LOG_INSTRUCTION) {
        printf("0x%08x: 0x%08x  %s %s,#%d\n",
               get_reg_data(15),
               opcode,
               ALU_as_string(MOV),
               register_as_string(reg_d),
               nn);
    }
    Arithmetic_MOV_Immediate(reg_d, nn);
    set_pc(get_reg_data(15) + 2);

}

void THUMB_cmp(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13)) >> 13;
    debug_assert(check_1 == 0x1, "check_1 must be 0x1 for this instruction");

    ARM_U_WORD reg_d = (opcode & (BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD nn = (opcode & (0xff));
    if (log_level & LOG_INSTRUCTION) {
        printf("0x%08x: 0x%08x  %s %s,#%d",
               get_reg_data(15),
               opcode,
               ALU_as_string(CMP),
               register_as_string(reg_d),
               nn);
    }
    Arithmetic_CMP_Immediate(reg_d, nn);
}

void THUMB_add_imm(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13)) >> 13;
    debug_assert(check_1 == 0x1, "check_1 must be 0x1 for this instruction");

    ARM_U_WORD op = (opcode & (BIT12 | BIT11)) >> 11;
    ARM_U_WORD reg_d = (opcode & (BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD nn = (opcode & (0xff));
    if (log_level & LOG_INSTRUCTION) {
        printf("0x%08x: 0x%08x  %s %s,#%d",
               get_reg_data(15),
               opcode,
               ALU_as_string(ADD),
               register_as_string(reg_d),
               nn);
    }

    Arithmetic_ADD_Immediate(reg_d, reg_d, nn);
}

void THUMB_sub_imm(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_ALU(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_high_register(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10)) >> 10;
    debug_assert(check_1 == 0x11, "Check_1 must be 0x11 for this instruction");

    ARM_U_WORD op = (opcode & (BIT9 | BIT8)) >> 8;
    bool MSBd = (opcode & (BIT7)) >> 7;
    bool MSBs = (opcode & (BIT6)) >> 6;
    ARM_U_WORD reg_s = (opcode & (BIT5 | BIT4 | BIT3)) >> 3;
    if (MSBs) {
        reg_s += 8;
    }
    ARM_U_WORD reg_s_data = get_reg_data(reg_s);
    ARM_U_WORD reg_d = (opcode & (BIT2 | BIT1 | BIT0));
    ARM_U_WORD reg_d_data = get_reg_data(reg_d);
    ARM_U_WORD result;
    if (op >= 0x0 && op <= 0x2) {
        debug_assert(MSBd || MSBs, "MSBd and MSBs cannot both be cleared for this instruction");
    }
    /**
     * ADD -> Rd=Rd+ Rs
     */
    if (op == 0x0) {
        result = reg_d_data + reg_s_data;
        printf("0x%08x: 0x%08x  %s  %s,%s\n", get_reg_data(15), opcode, ALU_as_string(ADD), register_as_string(reg_d),
               register_as_string(reg_s));

        set_reg(reg_d, result);
        set_pc(get_reg_data(15) + 2);

    }
        /**
         * CMP
         */
    else if (op == 0x1) {
        printf("0x%08x: 0x%08x  %s  %s,%s\n", get_reg_data(15), opcode, ALU_as_string(CMP), register_as_string(reg_d),
               register_as_string(reg_s));
        Arithmetic_CMP_Immediate(reg_d, reg_s_data);
        set_pc(get_reg_data(15) + 2);

    }
        /**
         * MOV OR NOP
         */
    else if (op == 0x2) {
        printf("0x%08x: 0x%08x  %s  %s,%s\n", get_reg_data(15), opcode, ALU_as_string(MOV), register_as_string(reg_d),
               register_as_string(reg_s));
        set_reg(reg_d, reg_s_data);
        set_pc(get_reg_data(15) + 2);
    }
        /**
         * BX
         */
    else {
        debug_assert(MSBd == 0x0, "MSBd must not be set for bx");
        printf("0x%08x: 0x%04x  BX %s\n", get_reg_data(15), opcode, register_as_string(reg_s));
        ARM_U_WORD target_address = get_reg_data(reg_s);
        if (reg_s_data & BIT0) {
            cpsr.T_state_bit = 1;
        } else {
            cpsr.T_state_bit = 0;
        }
        if (target_address % 2 == 0) {
            puts("Data aligned\n");
        } else {
            puts("Data not aligned\n");
            target_address &= 0xfffffffe;
            printf("Re-aligned target address to 0x%08x on half-word alignment\n", target_address);
        }
        set_reg(15, target_address);
    }

}

void THUMB_load_pc(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11;
    debug_assert(check_1 == 0x9, "Bits 15-11 must be 0x9");

    ARM_U_WORD reg_d = (opcode & (BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD u8_off = (opcode & 0xff)<<2;

    ARM_U_WORD pc_data =(get_reg_data(15)+4) & (~2);
    ARM_U_WORD load_addr = pc_data + u8_off;


    printf("0x%08x: 0x%04x LDR %s, [0x%08x]\n",get_reg_data(15),opcode,register_as_string(reg_d),load_addr);
    ARM_U_WORD retval = read_memory(load_addr,WORD);
    set_reg(reg_d,retval);
    set_reg(15,get_reg_data(15)+2);
}

void THUMB_store_reg(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_load_reg(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_store_sign_extend(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_load_sign_extend(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_store_imm(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_load_imm(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_store_hword(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_load_hword(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_store_sp_relative(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_load_sp_relative(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_push(ARM_U_WORD opcode) {
    ARM_U_WORD check_1 = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12;
    debug_assert(check_1 == 0xb, "Check_1 must be 0xb for this instruction");
    bool operation = (opcode & (BIT11)) >> 11;
    debug_assert(operation == false, "THUMB_push should only be called when bit 11 is false [PUSH]");
    ARM_U_WORD check_2 = (opcode & (BIT10 | BIT9)) >> 9;
    debug_assert(check_2 == 0x2, "Check_2 must be 0x2 for this instruction");
    bool use_pc_lr = (opcode & (BIT8)) >> 8;

    ARM_U_WORD Rlist = (opcode & (0xff));
    if (log_level & LOG_INSTRUCTION) {
        char register_list[20];
        ARM_U_WORD index = 0;
        for (ARM_S_BYTE reg = 0; reg < 0x8; reg += 1) {
            if (Rlist & (1 << reg)) {
                register_list[index] = 'r';
                register_list[index + 1] = reg + 0x30;
                register_list[index + 2] = ',';
                index += 3;
            }
        }
        register_list[index - 1] = '\0';
        printf("0x%08x: 0x%04x  PUSH {%s%s}\n", get_reg_data(15), opcode, register_list, use_pc_lr ? ",lr" : "");
    }
    if (use_pc_lr) {
        push_reg(14);
    }
    for (ARM_S_BYTE reg = 8; reg >= 0; reg -= 1) {
        if (Rlist & (1 << reg)) {
            push_reg(reg);
        }
    }
    set_reg(15, get_reg_data(15) + 2);
}

void THUMB_pop(ARM_U_WORD opcode) {
    printf("Placeholder\n");
}

void THUMB_multiple_load_store(ARM_U_WORD opcode) {
    printf("Multiple load/store\n");
}

void THUMB_conditional_branch(ARM_U_WORD opcode) {
    printf("conditional branch\n");
}

void THUMB_unconditional_branch(ARM_U_WORD opcode) {
    printf("unconditional branch\n");
}

void THUMB_long_branch_link_upper(ARM_U_WORD opcode) {
    debug_assert((opcode & BIT0) == 0x0, "Bit 0 must be 0 for this instruction");
    ARM_U_WORD instr_upper = (opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11;
    debug_assert(instr_upper == 0x1e, "upper 6 bits must be 0x1e for this instruction");
    ARM_U_WORD upper_nn = (opcode & (BIT10 | BIT9 | BIT8 | 0xff));
    printf("0x%08x: 0x%04x %s %s,%s + 4 + (0x%04x %s 12)  BL: LONG JUMP WITH LINK, NEXT INSTRUCTION HAS FULL TARGET ADDRESS\n",
           get_reg_data(15),
           opcode, ALU_as_string(MOV),
           register_as_string(14),
           register_as_string(15),
           upper_nn,
           shift_as_string(LSL));
    upper_nn = Shift(upper_nn, 12, LSL);
    upper_nn += 4;
    upper_nn += get_reg_data(15);

    set_reg(14, upper_nn);
    set_reg(15, get_reg_data(15) + 2);
}

void THUMB_long_branch_link_lower(ARM_U_WORD opcode) {
    ARM_U_WORD lower_nn = (opcode & (BIT10 | BIT9 | BIT8 | 0xff));
    printf("%18s %s %s,%s + (0x%04x %s 1)\n",
           "",
           ALU_as_string(MOV),
           register_as_string(15),
           register_as_string(14),
           lower_nn,
           shift_as_string(LSL));
    printf("0x%08x: 0x%04x %s %s,%s +2\n",
           get_reg_data(15),
           opcode, ALU_as_string(MOV),
           register_as_string(14),
           register_as_string(15));
    lower_nn = Shift(lower_nn, 1, LSL);
    //lower_nn += 2;
    ARM_U_WORD current_pc_data = get_reg_data(15) + 3;
    lower_nn += get_reg_data(14);

    set_reg(15, lower_nn);
    set_reg(14, current_pc_data);

}

void THUMB_software_interrupt(ARM_U_WORD opcode) {
    ARM_U_WORD nn = (opcode & (0xff));
    printf("0x%08x: 0x%04x  swi #%d\n", get_reg_data(15), opcode, nn);
    set_reg(15, get_reg_data(15) + 2);
}

ALU_Opcode_Alias get_ALU_opcode_alias(ARM_U_WORD opcode) {
    switch (opcode) {
        case AND:
            return AND;
        case XOR:
            return XOR;
        case SUB:
            return SUB;
        case RSB:
            return RSB;
        case ADD:
            return ADD;
        case ADC:
            return ADC;
        case SBC:
            return SBC;
        case RSC:
            return RSC;
        case TST:
            return TST;
        case TEQ:
            return TEQ;
        case CMP:
            return CMP;
        case CMN:
            return CMN;
        case ORR:
            return ORR;
        case MOV:
            return MOV;
        case BIC:
            return BIC;
        case MVN:
            return MVN;
    }
}

Condition_Alias get_condition_alias(ARM_U_WORD opcode) {
    switch (opcode) {

        case EQ:
            return EQ;
        case NE:
            return NE;
        case CS:
            return CS;
        case CC:
            return CC;
        case MI:
            return MI;
        case PL:
            return PL;
        case VS:
            return VS;
        case VC:
            return VC;
        case HI:
            return HI;
        case LS:
            return LS;
        case GE:
            return GE;
        case LT:
            return LT;
        case GT:
            return GT;
        case LE:
            return LE;
        case AL:
            return AL;
    }
    return AL;
}


void update_condition_flag(bool condition_flag) {
    printf("Condition flag set from %s to %s\n", current_condition_flag ? "true" : "false",
           condition_flag ? "true" : "false");
    current_condition_flag = condition_flag;
}

/**
 * @todo Implement Data Processing Immediate  opcode
 * @body Implement DataProc_Imm  for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void DataProc_Imm(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);
    ARM_U_WORD check = (opcode & (BIT27 | BIT26)) >> 26;

    debug_assert(check == 0x0, "Check must be 0x0 for this instruction");

    bool immediate = (opcode & (BIT25));
    debug_assert(immediate, "is_immediate is false when opcode should be is_immediate=true");
    ARM_U_WORD instruction = (opcode & (BIT24 | BIT23 | BIT22 | BIT21)) >> 21;
    ALU_Opcode_Alias instr_alias = get_ALU_opcode_alias(instruction);
    bool condition_flag = (opcode & (BIT20)) >> 20;
    update_condition_flag(condition_flag);
    debug_assert(((instruction < 0x8) || (instruction > 0xb)) ||
                 (instruction <= 0xb && instruction >= 0x8 && !condition_flag),
                 "condition_flag is false when opcode should be set_condition_flag=true");

    ARM_U_WORD reg_n = (opcode & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16; //1st Operand Register - Includes PC=15
    ARM_U_WORD reg_d = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12; //Destination Register - Includes PC=15
    ARM_U_WORD reg_n_data = get_reg_data(reg_n);
    if (reg_n == 15) {
        reg_n_data += 8;
    }
    if (instr_alias >= TST && instr_alias <= CMN) {
        debug_assert((reg_d == 0x0 || reg_d == 0xf),
                     "Bad destination register, needs to be either reg[0] or reg[15]");
    }
    ARM_U_WORD Is = (opcode & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD nn = (opcode & (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0));
    ARM_U_WORD nn_shifted = Shift(nn, Is, ROR);
#ifdef _BUILD_WITH_LOGGING
    if (log_level & LOG_INSTRUCTION) {
        if ((instruction >= 0x0 && instruction <= 0x7) || instruction == 0xc || instruction == 0xe) {
            printf("0x%08x: 0x%08x\t%s %s %s,%s, #%d\n",
                   pc.r15.data,
                   opcode,
                   ALU_as_string(instruction),
                   condition_as_string(condition_alias),
                   register_as_string(reg_d),
                   register_as_string(reg_n),
                   nn_shifted);
        } else if (instruction == 0xd || instruction == 0xf) {
            printf("0x%08x: 0x%08x\t%s %s %s, #%d\n",
                   pc.r15.data,
                   opcode,
                   ALU_as_string(instruction),
                   condition_as_string(condition_alias),
                   register_as_string(reg_d), nn_shifted);
        }
    }
    if (log_level & LOG_OPCODE) {
        printf("Opcode: [DataProc_Imm|0x%08x]\nBinary format:\n", opcode);
        print_binary(opcode);
        printf("Condition: 0x%x\n"
               "Check: 0x%x\n"
               "reg_n: %d reg_n.data=[0x%08x]\n"
               "reg_d: %d reg_d.data=[0x%08x]\n"
               "Is: 0x%x\n"
               "nn: 0x%01x\n"
               "nn_shifted: 0x%08x\n", condition, check, reg_n, gpr.registers[reg_n].data, reg_d,
               gpr.registers[reg_n].data, Is, nn, nn_shifted);
    }
#endif
    bool pass_condition = check_condition(condition_alias);
    if (pass_condition) {
        switch (instruction) {
            case 0x0:
                Arithmetic_AND_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x1:
                Arithmetic_EOR_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x2:
                Arithmetic_SUB_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x3:
                Arithmetic_RSB_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x4:
                Arithmetic_ADD_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x5:
                Arithmetic_ADC_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x6:
                Arithmetic_SBC_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x7:
                Arithmetic_RSC_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0x8:
                Arithmetic_TST_Immediate(reg_n, nn_shifted);
                break;
            case 0x9:
                Arithmetic_TEQ_Immediate(reg_n, nn_shifted);
                break;
            case 0xa:
                Arithmetic_CMP_Immediate(reg_n, nn_shifted);
                break;
            case 0xb:
                Arithmetic_CMN_Immediate(reg_n, nn_shifted);
                break;
            case 0xc:
                Arithmetic_ORR_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0xd:
                Arithmetic_MOV_Immediate(reg_d, nn_shifted);
                break;
            case 0xe:
                Arithmetic_BIC_Immediate(reg_d, reg_n_data, nn_shifted);
                break;
            case 0xf:
                Arithmetic_MVN_Immediate(reg_n, nn_shifted);
                break;
        }
    }
    set_pc(get_reg_data(0xf) + 4);
}

/**
 * @todo Implement Data Processing Register  opcode
 * @body Implement DataProc_Reg  for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void DataProc_Reg(ARM_U_WORD opcode) {
    ARM_U_WORD condition = (opcode & (BIT31 | BIT30 | BIT29 | BIT28)) >> 28;
    Condition_Alias condition_alias = get_condition_alias(condition);
    ARM_U_WORD check = (opcode & (BIT27 | BIT26)) >> 26;

    debug_assert(check == 0x0, "Check must be 0x0 for this instruction");

    bool immediate = (opcode & (BIT25));
    debug_assert(!immediate, "is_immediate is true when opcode should be is_immediate=false");
    ARM_U_WORD instruction = (opcode & (BIT24 | BIT23 | BIT22 | BIT21)) >> 21;
    ALU_Opcode_Alias instr_alias = get_ALU_opcode_alias(instruction);
    bool condition_flag = (opcode & (BIT20)) >> 20;
    update_condition_flag(condition_flag);
    debug_assert(((instruction < 0x8) || (instruction > 0xb)) ||
                 (instruction <= 0xb && instruction >= 0x8 && !condition_flag),
                 "condition_flag is false when opcode should be set_condition_flag=true");
    ARM_U_WORD reg_n = (opcode & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16; //1st Operand Register - Includes PC=15
    ARM_U_WORD reg_d = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12; //Destination Register - Includes PC=15
    ARM_U_WORD reg_n_data = get_reg_data(reg_n);
    if (reg_n == 15) {
        reg_n_data += 8;
    }
    if (instr_alias >= TST && instr_alias <= CMN) {
        debug_assert((reg_d == 0x0 || reg_d == 0xf),
                     "Bad destination register, needs to be either reg[0] or reg[15]");
    }
    bool R = (opcode & (BIT4)) >> 4;
    ARM_U_WORD shift_type = (opcode & (BIT6 | BIT5)) >> 5;
    Shift_Type shift_alias = get_shift_alias(shift_type);
    ARM_U_WORD reg_m = (opcode & (BIT3 | BIT2 | BIT1 | BIT0));
    ARM_U_WORD reg_m_data = get_reg_data(reg_m);
    if (log_level & LOG_INSTRUCTION) {

        if ((instruction >= 0x0 && instruction <= 0x7) || instruction == 0xc || instruction == 0xe) {
            printf("0x%08x: 0x%08x\t%s %s %s,%s, #%d\n",
                   pc.r15.data,
                   opcode,
                   ALU_as_string(instruction),
                   condition_as_string(condition_alias),
                   register_as_string(reg_d),
                   register_as_string(reg_n),
                   reg_m_data);
        } else if (instruction == 0xd || instruction == 0xf) {
            printf("0x%08x: 0x%08x\t%s %s %s,%s\n",
                   pc.r15.data,
                   opcode,
                   ALU_as_string(instruction),
                   condition_as_string(condition_alias),
                   register_as_string(reg_d), register_as_string(reg_m));
        }
    }
    if (log_level & LOG_INSTRUCTION) {

    }
    if (R) {
        if (reg_m == 15) {
            if (!immediate) {
                reg_m_data += 12;
            }
        }
        ARM_U_WORD reg_s = (opcode & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8;
        ARM_U_WORD check_2 = (opcode & (BIT7)) >> 7;
        debug_assert(check_2 == 0x0, "Reserved bit 7 must be 0 for this instruction");

    } else {
        if (reg_m == 15) {
            reg_m_data += 8;
        }
        ARM_U_WORD shift_amount = (opcode & (BIT11 | BIT10 | BIT9 | BIT8 | BIT7));
        ARM_U_WORD data_with_offset = Shift(reg_m_data, shift_amount,
                                            shift_alias);
        switch (instr_alias) {

            case AND:
                break;
            case XOR:
                break;
            case SUB:
                break;
            case RSB:
                break;
            case ADD:
                break;
            case ADC:
                break;
            case SBC:
                break;
            case RSC:
                break;
            case TST:
                break;
            case TEQ:
                break;
            case CMP:
                break;
            case CMN:
                break;
            case ORR:
                break;
            case MOV:
                Arithmetic_MOV_Immediate(reg_d, data_with_offset);
                //set_reg(reg_d, data_with_offset);
                break;
            case BIC:
                break;
            case MVN:
                break;
        }
    }
    set_pc(get_reg_data(15) + 4);

}

/**
 * @todo Implement Data Processing Shift  opcode
 * @body Implement DataProc_Shift  for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void DataProc_Shift(ARM_U_WORD opcode) {
    printf("DataProc_Shift occurs here\n");

}

void undefined_opcode(ARM_U_WORD opcode) {
    printf("Undefined opcode occurs here\n");
}

void unknown_opcode(ARM_U_WORD opcode) {
    printf("Completely unknown opcode @[0x%08x]\n", opcode);
}

void decode(ARM_U_WORD opcode) {

    if (log_level & LOG_REGISTER) {
        print_gen_reg();
        print_cpsr();
    }
    /**
     * A32 instruction mode
     */
    if (cpsr.T_state_bit == false) {
        ARM_U_WORD o_type = (opcode & (BIT27 | BIT26 | BIT25 | BIT24)) >> 24;

        /**
         * @todo Rework this jump table to be cleaner/concise
         * @body This section requires @Cleanup to make it more concise
         */
        switch (o_type) {
            //SWI if 1111
            case 0xf:
                software_interrupt(opcode);
                break;
                // CoRegTrans/CoDataOp if 1110
            case 0xe:
                if (opcode & (BIT4)) {
                    //Coprocessor register operation
                    CoRegTrans(opcode);
                } else {
                    //Coprocessor data operation
                    CoDataOp(opcode);
                }
                break;
            case 0x3:
                if ((opcode & (BIT23 | BIT21 | BIT20)) >> 20 == 0x2) {
                    PSR_Imm(opcode);
                    break;
                } else {
                    goto exit_switch;
                }

                // case 0x1:
                //PSR_Reg(opcode);
                //    break;
                //The rest of the opcodes markers are only 3 bits wide for this section
            exit_switch:

            default:
                o_type = o_type >> 1;
                switch (o_type) {
                    //CoDataTrans if 110
                    case 0x6:
                        //Coprocessor data transfer
                        CoDataTrans(opcode);
                        break;
                    case 0x5:
                        Branch(opcode);
                        //Branch
                        break;
                    case 0x4:
                        BlockTrans(opcode);
                        //Block data transfer
                        break;
                    case 0x3:
                        /**
                         * @todo Test whether this check can actually distinguish undefined opcode vs single data transfer opcode
                         * @body The @Opcode formats for undefined and single data transfer are very similar and I'm not exactly sure
                         * how to distinguish either
                         */
                        if ((o_type & BIT4) >> 4) {
                            undefined_opcode(opcode);
                        } else {
                            TransReg9(opcode);
                        }
                        break;
                    case 0x2:
                        //Transfer immediate 9
                        TransImm9(opcode);
                        break;
                    case 0x1:
                        //Data Processing Immediate
                        DataProc_Imm(opcode);
                        break;
                    case 0x0:
                        //TransImm10
                        if (((opcode & BIT22) >> 22) && ((opcode & BIT7) >> 7 && ((opcode & BIT4) >> 4))) {
                            TransImm10(opcode);
                        }

                            //TransReg10
                        else if (!((opcode & BIT22) >> 22) && ((opcode & (BIT8 | BIT9 | BIT10 | BIT11)) >> 8 == 0x0) &&
                                 ((opcode & BIT7) >> 7) && ((opcode & BIT4) >> 4)) {
                            TransReg10(opcode);
                        }

                            //TransSwp12
                        else if (((opcode & (BIT24 | BIT25)) >> 24 == 0x2) &&
                                 ((opcode & (BIT21 | BIT22)) >> 21 == 0x0) &&
                                 ((opcode & (BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11)) >> 4 == 0x9)) {
                            TransSwp12(opcode);
                        }
                            //MulLong
                        else if (((opcode & (BIT23 | BIT24)) >> 23 == 0x1) &&
                                 ((opcode & (BIT4 | BIT5 | BIT6 | BIT7)) >> 4 == 0x9)) {
                            MulLong(opcode);
                        }
                            //Multiply
                        else if (((opcode & (BIT22 | BIT23 | BIT24)) >> 22 == 0x0) &&
                                 ((opcode & (BIT4 | BIT5 | BIT6 | BIT7)) >> 4 == 0x9)) {
                            Multiply(opcode);
                        }
                            //Branch Exchange
                        else if ((opcode & (0x012FFF10)) == 0x012FFF10) {
                            BranchExchange(opcode);
                        }
                            //PSR Register
                        else if ((opcode & 0x0F900FF0) == BIT24) {
                            PSR_Reg(opcode);
                        }
                            //PSR Immediate
                        else if ((opcode & 0x03200000) == 0x03200000) {
                            PSR_Imm(opcode);
                        }

                            //Data Processing Register
                        else if (((opcode & (BIT27 | BIT26 | BIT25 | BIT4))) == 0x0) {
                            DataProc_Reg(opcode);
                        }
                            //Data Processing Shift
                        else if (((opcode & (BIT27 | BIT26 | BIT25 | BIT7 | BIT4)) >> 4) == 0x1) {
                            DataProc_Shift(opcode);
                        } else {

                            unknown_opcode(opcode);
                        }
                        break;

                    default:
                        unknown_opcode(opcode);
                }
        }
    }
        /**
         * THUMB instruction mode
         */
    else {
        print_binary_THUMB(opcode);
        if (((opcode & (BIT15 | BIT14 | BIT13)) >> 13) == 0x0) {
            THUMB_move_shifted_register(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11) == 0x3) {
            ARM_U_WORD type = (opcode & (BIT10 | BIT9)) >> 9;
            if (type == 0x0 || type == 0x2) {
                THUMB_add(opcode);
            } else if (type == 0x1 || type == 0x3) {
                THUMB_subtract(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13)) >> 13) == 0x1) {
            ARM_U_WORD type = (opcode & (BIT12 | BIT11)) >> 11;
            if (type == 0x0) {
                THUMB_move(opcode);

            } else if (type == 0x1) {
                THUMB_cmp(opcode);
            } else if (type == 0x2) {
                THUMB_add_imm(opcode);
            } else if (type == 0x3) {
                THUMB_sub_imm(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10)) >> 10) == 0x10) {
            THUMB_ALU(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10)) >> 10) == 0x11) {
            THUMB_high_register(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11) == 0x9) {
            THUMB_load_pc(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0x5) {
            ARM_U_WORD type = ((opcode & (BIT11 | BIT10)) >> 10);
            if (((opcode & (BIT9)) >> 9) == 0x0) {
                if (type == 0x0 || type == 0x1) {
                    THUMB_load_reg(opcode);
                } else if (type == 0x2 || type == 0x3) {
                    THUMB_store_reg(opcode);
                }
            } else {
                if (type == 0x0 || type == 0x1) {
                    THUMB_load_sign_extend(opcode);
                } else if (type == 0x2 || type == 0x3) {
                    THUMB_store_sign_extend(opcode);
                }
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13)) >> 13) == 0x3) {
            ARM_U_WORD type = ((opcode & (BIT11 | BIT10)) >> 10);
            if (type == 0x0 || type == 0x1) {
                THUMB_load_imm(opcode);
            } else if (type == 0x2 || type == 0x3) {
                THUMB_store_imm(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0x8) {
            if ((opcode & (BIT11)) == 0x0) {
                THUMB_store_hword(opcode);
            } else {
                THUMB_load_hword(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0x9) {
            if ((opcode & (BIT11)) >> 11) {
                THUMB_load_sp_relative(opcode);
            } else {
                THUMB_store_sp_relative(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0xb) {
            if ((opcode & (BIT11)) >> 11) {
                THUMB_pop(opcode);
            } else {
                THUMB_push(opcode);
            }
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0xc) {
            THUMB_multiple_load_store(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12) == 0xd &&
                   (((opcode & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8) != 0xf)) {
            THUMB_conditional_branch(opcode);
        } else if (((opcode & (BIT15 | BIT14 | BIT13 | BIT12 | BIT11)) >> 11) == 0x1c) {
            THUMB_unconditional_branch(opcode);
        } else if (((opcode & 0xff00) >> 8) == 0xdf) {
            THUMB_software_interrupt(opcode);
        } else {
            bool branch_type = (opcode & (BIT11)) >> 11;
            if (!branch_type) {
                THUMB_long_branch_link_upper(opcode);
            } else {
                THUMB_long_branch_link_lower(opcode);
            }
        }
    }
}
