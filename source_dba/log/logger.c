//
// Created by johnm on 5/10/2020.
//

#include "logger.h"


/**
 * CPU initialization logging function
 */
void cpu_init_log() {
    printf("----------------CPU INIT LOG----------------\n");

    print_gen_reg();
    print_program_counter();
    print_stack_pointer();
    print_link_register();
    print_program_counter();
    print_cond_flag();
    print_cpsr();
}

void print_program_counter() {
    printf("----------------Program Counter (PC)----------------\n");
    printf("r15: [0x%08x] ---> [0x%08x]\n", pc.r15.data, MEMORY[pc.r15.data]);
}

void print_stack_pointer() {
    printf("----------------Stack Pointer (SP)----------------\n");
    printf("r14: [0x%08x] ---> [0x%08x]\n", sp.r13.data, MEMORY[sp.r13.data]);
}

void print_link_register() {
    printf("----------------Link Register (LR)----------------\n");
    printf("r14: [0x%08x] ---> [0x%08x]\n", lr.r14.data, MEMORY[lr.r14.data]);
}

void log_err(Error_Message err) {
    printf("Erro code %d: %s\n", err.code, err.error_msg);
}

void print_gen_reg() {
    printf("----------------General Purpose Registers (GPR)----------------\n");
    printf("%5s[0x%08x]", "r0: ", gpr.registers[0].data);
    printf("%8s[0x%08x]", "r1: ", gpr.registers[1].data);
    printf("%8s[0x%08x]\n", "r2: ", gpr.registers[2].data);
    printf("%5s[0x%08x]", "r3: ", gpr.registers[3].data);
    printf("%8s[0x%08x]", "r4: ", gpr.registers[4].data);
    printf("%8s[0x%08x]\n", "r5: ", gpr.registers[5].data);
    printf("%5s[0x%08x]", "r6: ", gpr.registers[6].data);
    printf("%8s[0x%08x]", "r7: ", gpr.registers[7].data);
    printf("%8s[0x%08x]\n", "r8: ", gpr.registers[8].data);
    printf("%5s[0x%08x]", "r9: ", gpr.registers[9].data);
    printf("%8s[0x%08x]", "r10: ", gpr.registers[10].data);
    printf("%8s[0x%08x]\n", "r11: ", gpr.registers[11].data);
    printf("%5s[0x%08x]\n", "r12: ", gpr.registers[12].data);

}

//TODO Update to use format specifiers
void print_cond_flag() {
    printf("----------------Conditional Flags init values----------------\n");
    printf("EQ: [%d]", cond_flags.EQ);
    printf("\tNE: [%d]", cond_flags.NE);
    printf("\t CS/HS: [%d]", cond_flags.CS_HS);
    printf("\t CC/LO: [%d]\n", cond_flags.CC_LO);
    printf("MI: [%d]", cond_flags.MI);
    printf("\tPL: [%d]", cond_flags.PL);
    printf("\t\tVS: [%d]", cond_flags.VS);
    printf("\t\tVC: [%d]\n", cond_flags.VC);
    printf("HI: [%d]", cond_flags.HI);
    printf("\tLS: [%d]", cond_flags.LS);
    printf("\t\tGE: [%d]", cond_flags.GE);
    printf("\t\tLT: [%d]\n", cond_flags.LT);
    printf("GT: [%d]", cond_flags.GT);
    printf("\tLE: [%d]", cond_flags.LE);
    printf("\t\tAL: [%d]", cond_flags.AL);
    printf("\t\tNV: [%d]\n", cond_flags.NV);


}
/**
 * Prints MSB->LSB contents of the CPSR
 */
//TODO Update to use format specifiers

void print_cpsr() {
    printf("----------------Current Program Status Register (CPSR)----------------\n");
    printf("N - Sign Flag: [%d] ---- (0=Not Signed, 1=Signed)\n", cpsr.N_Sign_flag);
    printf("Z - Zero Flag: [%d] ---- (0=Not Zero, 1=Zero)  \n", cpsr.Z_Zero_flag);
    printf("C - Carry Flag: [%d]\n", cpsr.C_Carry_flag);

}

void logger(const char *tag, const char *message) {
    time_t now;
    time(&now);
    printf("%s [%s]: %s\n", ctime(&now), tag, message);
}

void log_msg(General_Message msg) {
    time_t now;
    time(&now);
    printf("Instruction: %s @ time: %s\n%s",msg.instruction_name,ctime(&now),msg.log);
}
