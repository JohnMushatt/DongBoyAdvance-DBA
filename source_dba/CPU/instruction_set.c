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
    printf("\n\n");
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

void Arithmetic_AND_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD immediate) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data & immediate;
    if (current_condition_flag) {

    }
}

void Arithmetic_EOR_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD immediate) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data ^ immediate;
}

void Arithmetic_SUB_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data - Op2;
}

void Arithmetic_RSB_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = Op2 - gpr.registers[reg_n].data;
}

void Arithmetic_ADD_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data + Op2;
}

void Arithmetic_ADC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data + Op2 + cpsr.C_Carry_flag;
}

void Arithmetic_SBC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data - Op2 + cpsr.C_Carry_flag - 1;
}

void Arithmetic_RSC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = Op2 - gpr.registers[reg_n].data + cpsr.C_Carry_flag - 1;
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

void Arithmetic_ORR_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data | Op2;
}

void Arithmetic_MOV_Immediate(ARM_U_WORD reg_d, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = Op2;
}

void Arithmetic_BIC_Immediate(ARM_U_WORD reg_d, ARM_U_WORD reg_n, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = gpr.registers[reg_n].data & ~(Op2);
}

void Arithmetic_MVN_Immediate(ARM_U_WORD reg_d, ARM_U_WORD Op2) {
    gpr.registers[reg_d].data = ~(Op2);
}

/**
 * ALU IMMEDIATE UTILITY INSTRUCTIONS
 */
ARM_U_WORD ROR_RRX_Imm(ARM_U_WORD immediate) {
    return 0;
}

ARM_U_WORD ROR_Imm(ARM_U_WORD immediate, ARM_U_WORD shift_amount) {
    ARM_U_WORD operand = immediate;
    if (shift_amount == 0) {
        ROR_RRX_Imm(immediate);
    }
    ARM_U_WORD operand_mask = (1 << shift_amount) - 1;
    ARM_U_WORD leftover_mask = operand_mask ^0xffffffff;
    ARM_U_WORD result = (operand & operand_mask) << ((sizeof(ARM_U_WORD) * 8) - shift_amount);
    printf("Performed ROR shift on immediate: imm=[0x%08x] operand_mask=[0x%08x] leftover_mask=[0x%08x] result=[0x%08x]\n",
           immediate, operand_mask, leftover_mask, result);
    return result;
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
    printf("Branch occurs here\n");
}

/**
 * @todo Implement Branch Exchange opcode
 * @body Implement BranchExchange for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void BranchExchange(ARM_U_WORD opcode) {
    printf("BranchExchange occurs here\n");

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
    ARM_U_WORD Offset = (opcode &
                         (BIT12 | BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0));

    char Bit_21_String[128];
    if (P) {
        sprintf(Bit_21_String, "W: %s;write-back is OPTIONAL", Write_Back ? "write address into base" : "no write-back");
    } else {
        sprintf(Bit_21_String, "T: %s;write-back is ALWAYS enabled", Memory_Management ? "1=Force non-privileged access" : "0=Normal");
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
           reg_n, gpr.registers[reg_n].data, reg_d,
           gpr.registers[reg_n].data, Offset);
    bool pass_condition = check_condition(condition_alias);
    if (pass_condition) {
        switch ((ARM_U_BYTE)L) {
            case false:
                break;
            case true:
                break;
            default:
                break;
        }
    }
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
    printf("PSR_Reg occurs here\n");
}

/**
 * @todo Implement PSR Immediate opcode
 * @body Implement PSR Imm for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void PSR_Imm(ARM_U_WORD opcode) {
    printf("PSR_Imm occurs here\n");

}

ALU_Opcode_Alias get_ALU_opcode_alias(ARM_U_WORD opcode) {
    switch (opcode) {
        case AND:
            return AND;
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
            return CMP;
        case CMN:
            break;
        case ORR:
            break;
        case MOV:
            break;
        case BIC:
            break;
        case MVN:
            break;
    }
}

Condition_Alias get_condition_alias(ARM_U_WORD opcode) {
    switch (opcode) {

        case EQ:
            return EQ;
            break;
        case NE:
            return NE;
            break;
        case CS:
            return CS;
            break;
        case CC:
            return CC;
            break;
        case MI:
            return MI;
            break;
        case PL:
            return PL;
            break;
        case VS:
            return VS;
            break;
        case VC:
            return VC;
            break;
        case HI:
            return HI;
            break;
        case LS:
            return LS;
            break;
        case GE:
            return GE;
            break;
        case LT:
            return LT;
            break;
        case GT:
            return GT;
            break;
        case LE:
            return LE;
            break;
        case AL:
            return AL;
            break;
    }
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
    debug_assert((instruction < 0x8) || (instruction <= 0xb && instruction >= 0x8 && !condition_flag),
                 "condition_flag is false when opcode should be set_condition_flag=true");

    ARM_U_WORD reg_n = (opcode & (BIT19 | BIT18 | BIT17 | BIT16)) >> 16; //1st Operand Register - Includes PC=15
    ARM_U_WORD reg_d = (opcode & (BIT15 | BIT14 | BIT13 | BIT12)) >> 12; //Destination Register - Includes PC=15
    if (instr_alias >= TST && instr_alias <= CMN) {
        debug_assert((reg_d == 0x0 || reg_d == 0xf),
                     "Bad destination register, needs to be either reg[0] or reg[15]");
    }
    ARM_U_WORD Is = (opcode & (BIT11 | BIT10 | BIT9 | BIT8)) >> 8;
    ARM_U_WORD nn = (opcode & (BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0));
    ARM_U_WORD nn_shifted = ROR_Imm(nn, Is);
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
    bool pass_condition = check_condition(condition_alias);
    if (pass_condition) {
        switch (instruction) {
            case 0x0:
                Arithmetic_AND_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x1:
                Arithmetic_EOR_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x2:
                Arithmetic_SUB_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x3:
                Arithmetic_RSB_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x4:
                Arithmetic_ADD_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x5:
                Arithmetic_ADC_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x6:
                Arithmetic_SBC_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0x7:
                Arithmetic_RSC_Immediate(reg_d, reg_n, nn_shifted);
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
                Arithmetic_ORR_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0xd:
                Arithmetic_MOV_Immediate(reg_d, nn_shifted);
                break;
            case 0xe:
                Arithmetic_BIC_Immediate(reg_d, reg_n, nn_shifted);
                break;
            case 0xf:
                Arithmetic_MVN_Immediate(reg_n, nn_shifted);
                break;
        }
    }
}

/**
 * @todo Implement Data Processing Register  opcode
 * @body Implement DataProc_Reg  for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void DataProc_Reg(ARM_U_WORD opcode) {
    printf("DataProc_Reg occurs here\n");

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


    ARM_U_WORD o_type = (opcode & (BIT27 | BIT26 | BIT25 | BIT24)) >> 24;
    /**
     * @todo Rework this jump table to be cleaner/concise
     * @body This section requires @Cleanup to make it more concise
     */
    switch (o_type) {
        //SWI if 1111
        case 0xf:
            /**
             * @todo Implement software interrupt
             * @body This is just a stub as of now, but it needs to be implemented @Feature
             */
            software_interrupt(opcode);
            break;
            // CoRegTrans/CoDataOp if 1110
        case 0xe:
            if ((opcode & (BIT4)) >> 4) {
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

            }
            break;
        case 0x1:
            PSR_Reg(opcode);
            //The rest of the opcodes markers are only 3 bits wide for this section
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
                    else if ((opcode & BIT24) == BIT24) {
                        PSR_Reg(opcode);
                    }
                        //PSR Immediate
                    else if ((opcode & 0x03200000) == 0x03200000) {
                        PSR_Imm(opcode);
                    }

                        //Data Processing Register
                    else if (((opcode & (BIT27 | BIT26 | BIT25 | BIT7 | BIT4))) == (BIT4)) {
                        DataProc_Reg(opcode);
                    }
                        //Data Processing Shift
                    else if (((opcode & (BIT27 | BIT26 | BIT25 | BIT4))) == 0x0) {
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
