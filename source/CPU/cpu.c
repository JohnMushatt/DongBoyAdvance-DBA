//
// Created by johnm on 5/10/2020.
//

#include "cpu.h"
#include "logger.h"
void init_cpu() {
    init_general_registers();
    init_conditional_flags();
    init_current_program_status_register();
    init_exception_vector_table();
    cpu_init_log();


}

void init_general_registers() {
    gpr_clear();
    pc.r15.data = 0x0;
    sp.r13.data = MAX_MEM-1;
}

void gpr_clear() {
    for (ARM_WORD i = 0; i < 13; i++) {
        gpr.registers[i].data = 0x0;
    }
}

void init_conditional_flags() {
    cond_flags.flags = 0;
}

void init_current_program_status_register() {
    cpsr.Mode_bits = 0x3;
    if (cpsr.status != 0x3) {
        Error_Message err = {"cpsr bits not set correctly", 0x100};
        log_err(err);
    }
    cpsr.N_Sign_flag = 1;
    if (cpsr.status >> 31 != 1) {
        Error_Message err = {"cpsr bits not set correctly", 0x100};
        log_err(err);
    }
    cpsr_clear();
}

void cpsr_clear() {
    cpsr.status = 0;
}

void init_exception_vector_table() {
    /**
     * Reset vector
     */
    exception_vector_table.Reset.address = (ARM_WORD) exception_vector_table.base + 0x00;
    exception_vector_table.Reset.interrupt_flags.I = set_1;
    exception_vector_table.Reset.interrupt_flags.F = set_1;
    exception_vector_table.Reset.priority = 1;
    exception_vector_table.Reset.mode_on_entry = _svc;
    /**
     * Undefined Instruction
     */
    exception_vector_table.Undefined_Instruction.address = (ARM_WORD) exception_vector_table.base + 0x04;
    exception_vector_table.Undefined_Instruction.interrupt_flags.I = set_1;
    exception_vector_table.Undefined_Instruction.interrupt_flags.F = no_change;
    exception_vector_table.Undefined_Instruction.priority = 7;
    exception_vector_table.Undefined_Instruction.mode_on_entry = _und;
    /**
     * Software Interrupt (SWI)
     */
    exception_vector_table.Software_Interrupt_SWI.address = (ARM_WORD) exception_vector_table.base + 0x08;
    exception_vector_table.Software_Interrupt_SWI.interrupt_flags.I = set_1;
    exception_vector_table.Software_Interrupt_SWI.interrupt_flags.F = no_change;
    exception_vector_table.Software_Interrupt_SWI.priority = 6;
    exception_vector_table.Software_Interrupt_SWI.mode_on_entry = _svc;
    /**
     * Prefect Abort
     */
    exception_vector_table.Prefect_Abort.address = (ARM_WORD) exception_vector_table.base + 0x0c;
    exception_vector_table.Prefect_Abort.interrupt_flags.I = set_1;
    exception_vector_table.Prefect_Abort.interrupt_flags.F = no_change;
    exception_vector_table.Prefect_Abort.priority = 5;
    exception_vector_table.Prefect_Abort.mode_on_entry = _abt;
    /**
     * Data Abort
     */
    exception_vector_table.Data_Abort.address = (ARM_WORD) exception_vector_table.base + 0x10;
    exception_vector_table.Data_Abort.interrupt_flags.I = set_1;
    exception_vector_table.Data_Abort.interrupt_flags.F = no_change;
    exception_vector_table.Data_Abort.priority = 2;
    exception_vector_table.Data_Abort.mode_on_entry = _abt;
    /**
     * Address Exceeds 26-bit (Most likely legacy support)
     */
    exception_vector_table.Address_Exceeds_26bit.address = (ARM_WORD) exception_vector_table.base + 0x14;
    exception_vector_table.Address_Exceeds_26bit.interrupt_flags.I = set_1;
    exception_vector_table.Address_Exceeds_26bit.interrupt_flags.F = no_change;
    exception_vector_table.Address_Exceeds_26bit.priority = 0;
    exception_vector_table.Address_Exceeds_26bit.mode_on_entry = _svc;
    /**
     * Normal Interrupt (IQR)
     */
    exception_vector_table.Normal_Interrupt_IQR.address = (ARM_WORD) exception_vector_table.base + 0x18;
    exception_vector_table.Normal_Interrupt_IQR.interrupt_flags.I = set_1;
    exception_vector_table.Normal_Interrupt_IQR.interrupt_flags.F = no_change;
    exception_vector_table.Normal_Interrupt_IQR.priority = 4;
    exception_vector_table.Normal_Interrupt_IQR.mode_on_entry = _iqr;
    /**
     * Fast Interrupt (FIQ)
     */
    exception_vector_table.Fast_Interrupt_FIQ.address = (ARM_WORD) exception_vector_table.base + 0x1c;
    exception_vector_table.Fast_Interrupt_FIQ.interrupt_flags.I = set_1;
    exception_vector_table.Fast_Interrupt_FIQ.interrupt_flags.F = set_1;
    exception_vector_table.Fast_Interrupt_FIQ.priority = 3;
    exception_vector_table.Fast_Interrupt_FIQ.mode_on_entry = _fiq;
}