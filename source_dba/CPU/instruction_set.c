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
    printf("Software Interrupt occurs here\n");
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
 * @todo Implement Transfer Register 9 opcode
 * @body Implement TransReg9 for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void TransReg9(ARM_U_WORD opcode) {
    printf("TransReg9 occurs here\n");
}
/**
 * @todo Implement Block Transfer opcode
 * @body Implement BlockTrans for the CPU @Feature,@Opcode
 * @param opcode 32-bit instruction to decode
 */
void BlockTrans(ARM_U_WORD opcode) {
    printf("BlockTrans occurs here\n");
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
            //The rest of the opcodes markers are only 3 bits wide for this section
        default:
            o_type = o_type >>1;
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
                case 0x1:
                    break;
                case 0x0:
                    //TransImm10
                    if (((o_type & BIT22) >> 22) && ((o_type & BIT7) >> 8 && ((o_type & BIT4) >> 4))) {
                        TransImm10(opcode);
                    }
                        //TransReg10
                    else if (!((o_type & BIT22) >> 22) && ((o_type & (BIT8 | BIT9 | BIT10 | BIT11)) >> 8 != 0x0) &&
                             ((o_type & BIT7) >> 8) && ((o_type & BIT4) >> 4)) {
                        TransReg10(opcode);
                    }
                    //TransSwp12
                    else if (((o_type & (BIT24 | BIT25)) >> 24 == 0x2) && ((o_type & (BIT21 | BIT22)) >> 21 == 0x0) &&
                               ((o_type & (BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11)) >> 4 == 0x9)) {
                        TransSwp12(opcode);
                    }
                    break;
                default:
                    unknown_opcode(opcode);
            }
    }


}
