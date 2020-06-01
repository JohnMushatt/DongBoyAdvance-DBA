//
// Created by johnm on 5/10/2020.
//

#include "cpu.h"

void init_cpu() {
    init_general_registers();
    init_conditional_flags();
    init_current_program_status_register();
    init_exception_vector_table();
    cpu_init_log();
    gpr_clear();
    clear_all_mem();

}
void clear_all_mem() {
    for(ARM_U_WORD i =0; i < MAX_MEM; i += sizeof(ARM_U_BYTE)) {
        MEMORY[i] = 0;
    }
}

void init_general_registers() {
    gpr_clear();
    pc.r15.data = 0x0;
    sp.r13.data = MAX_MEM - 1;
}

void gpr_clear() {
    for (ARM_U_WORD i = 0; i < 13; i++) {
        gpr.registers[i].data = 0x0;
    }
}

void init_conditional_flags() {
    cond_flags.flags = 0;
}

void init_current_program_status_register() {

    cpsr_clear();
}

void cpsr_clear() {
    cpsr.status = 0;
}

/**
 *
 * @param reg Number of registers to clear
 * @param ... Variable argument list containing registers to clear
 */
void zero_reg(int reg, ...) {
    va_list valist;
    va_start(valist, reg);
    for (ARM_U_WORD i = 0; i < reg; i++) {
        gpr.registers[va_arg(valist, int)].data = 0;
    }
    va_end(valist);
}

void set_reg(ARM_U_WORD reg, ARM_U_WORD val) {
    gpr.registers[reg].data = val;
}

void init_exception_vector_table() {
    /**
     * Reset vector
     */
    exception_vector_table.Reset.address = (ARM_U_WORD) exception_vector_table.base + 0x00;
    exception_vector_table.Reset.interrupt_flags.I = set_1;
    exception_vector_table.Reset.interrupt_flags.F = set_1;
    exception_vector_table.Reset.priority = 1;
    exception_vector_table.Reset.mode_on_entry = _svc;
    /**
     * Undefined Instruction
     */
    exception_vector_table.Undefined_Instruction.address = (ARM_U_WORD) exception_vector_table.base + 0x04;
    exception_vector_table.Undefined_Instruction.interrupt_flags.I = set_1;
    exception_vector_table.Undefined_Instruction.interrupt_flags.F = no_change;
    exception_vector_table.Undefined_Instruction.priority = 7;
    exception_vector_table.Undefined_Instruction.mode_on_entry = _und;
    /**
     * Software Interrupt (SWI)
     */
    exception_vector_table.Software_Interrupt_SWI.address = (ARM_U_WORD) exception_vector_table.base + 0x08;
    exception_vector_table.Software_Interrupt_SWI.interrupt_flags.I = set_1;
    exception_vector_table.Software_Interrupt_SWI.interrupt_flags.F = no_change;
    exception_vector_table.Software_Interrupt_SWI.priority = 6;
    exception_vector_table.Software_Interrupt_SWI.mode_on_entry = _svc;
    /**
     * Prefect Abort
     */
    exception_vector_table.Prefect_Abort.address = (ARM_U_WORD) exception_vector_table.base + 0x0c;
    exception_vector_table.Prefect_Abort.interrupt_flags.I = set_1;
    exception_vector_table.Prefect_Abort.interrupt_flags.F = no_change;
    exception_vector_table.Prefect_Abort.priority = 5;
    exception_vector_table.Prefect_Abort.mode_on_entry = _abt;
    /**
     * Data Abort
     */
    exception_vector_table.Data_Abort.address = (ARM_U_WORD) exception_vector_table.base + 0x10;
    exception_vector_table.Data_Abort.interrupt_flags.I = set_1;
    exception_vector_table.Data_Abort.interrupt_flags.F = no_change;
    exception_vector_table.Data_Abort.priority = 2;
    exception_vector_table.Data_Abort.mode_on_entry = _abt;
    /**
     * Address Exceeds 26-bit (Most likely legacy support)
     */
    exception_vector_table.Address_Exceeds_26bit.address = (ARM_U_WORD) exception_vector_table.base + 0x14;
    exception_vector_table.Address_Exceeds_26bit.interrupt_flags.I = set_1;
    exception_vector_table.Address_Exceeds_26bit.interrupt_flags.F = no_change;
    exception_vector_table.Address_Exceeds_26bit.priority = 0;
    exception_vector_table.Address_Exceeds_26bit.mode_on_entry = _svc;
    /**
     * Normal Interrupt (IQR)
     */
    exception_vector_table.Normal_Interrupt_IQR.address = (ARM_U_WORD) exception_vector_table.base + 0x18;
    exception_vector_table.Normal_Interrupt_IQR.interrupt_flags.I = set_1;
    exception_vector_table.Normal_Interrupt_IQR.interrupt_flags.F = no_change;
    exception_vector_table.Normal_Interrupt_IQR.priority = 4;
    exception_vector_table.Normal_Interrupt_IQR.mode_on_entry = _iqr;
    /**
     * Fast Interrupt (FIQ)
     */
    exception_vector_table.Fast_Interrupt_FIQ.address = (ARM_U_WORD) exception_vector_table.base + 0x1c;
    exception_vector_table.Fast_Interrupt_FIQ.interrupt_flags.I = set_1;
    exception_vector_table.Fast_Interrupt_FIQ.interrupt_flags.F = set_1;
    exception_vector_table.Fast_Interrupt_FIQ.priority = 3;
    exception_vector_table.Fast_Interrupt_FIQ.mode_on_entry = _fiq;
}

void write_memory(ARM_U_WORD address, ARM_U_WORD val, Write_Mode mode) {
    ARM_U_WORD temp;
    switch (mode) {
        case BYTE:
            MEMORY[address] = val;
            break;
        case HALF_WORD:
            break;
        case WORD:

            MEMORY[address] = (val & 0xff);
            val >>= 8;
            MEMORY[address + 1] = (val & 0xff);
            val >>= 8;
            MEMORY[address + 2] = (val & 0xff);
            val >>= 8;
            MEMORY[address + 3] = (val & 0xff);
            break;
        case DOUBLE_WORD:
            break;
    }
}

void view_address(ARM_U_WORD address, Read_Mode mode) {
    switch (mode) {
        ARM_U_WORD value;
        case BYTE:
            value = MEMORY[address];
            printf("Address: [0x%08x] | BYTE: [0x%08x]\n", address, value);
            break;

        case HALF_WORD:
            value = MEMORY[address] | MEMORY[address + 1];
            printf("Address: [0x%08x] | HALF WORD: [0x%08x]\n", address, MEMORY[address]);
            break;

        case WORD:
            value = MEMORY[address];
            value |= MEMORY[address + 1] << 8;
            value |= MEMORY[address + 2] << 16;
            value |= MEMORY[address + 3] << 24;
            printf("Address: [0x%08x] | WORD: [0x%08x]\n", address, value);
            break;
        case DOUBLE_WORD:
            break;
    }
}
ARM_U_WORD read_memory(ARM_U_WORD address,Read_Mode mode) {
    ARM_U_WORD data;
    switch (mode) {

        case BYTE:
            data=get_byte(address);
            break;
        case HALF_WORD:
            break;
        case WORD:
            data=get_word(address);
            break;
        case DOUBLE_WORD:
            break;
    }
    return data;
}
ARM_U_WORD get_word(ARM_U_WORD address) {
    ARM_U_WORD query = MEMORY[address];
    query |= MEMORY[address + 1] << 8;
    query |= MEMORY[address + 2] << 16;
    query |= MEMORY[address + 3] << 24;
    return query;
}
ARM_U_WORD get_byte(ARM_U_WORD address) {
    ARM_U_WORD query = MEMORY[address];
    return query;
}
/***
 *
 * @param starting_address Address to begin filling with random values
 * @param size Number of 4 byte blocks to fill
 */
void set_memory_range_random(ARM_U_WORD starting_address, ARM_U_WORD size, Write_Mode mode) {
    srand(0);
    ARM_U_WORD ending_address = starting_address + (size * sizeof(ARM_U_WORD));
    ARM_U_WORD offset;
    ARM_U_WORD range;
    switch (mode) {
        case BYTE:
            offset = sizeof(ARM_U_BYTE);
            range = 0xff;
            break;
        case HALF_WORD:
            offset = sizeof(ARM_U_HWORD);
            range = 0xffff;
            break;
        case WORD:
            offset = sizeof(ARM_U_WORD);
            range = 0xffffffff;
            break;
        case DOUBLE_WORD:
            offset = sizeof(ARM_U_DWORD);
            range = 0xffffffff;
            break;
        default:
            offset = sizeof(ARM_U_BYTE);
            range = 0xff;
    }
    printf("Starting write at [0x%08x], size: %u, offset: %u\n", starting_address, size, offset);

    ARM_U_WORD random_number;
    for (ARM_U_WORD i = starting_address; i < ending_address; i += offset) {
        random_number = rand() % range;
        write_memory(i, random_number, mode);

    }
    for (ARM_U_WORD i = starting_address; i < ending_address; i += offset) {
        view_address(i, WORD);
    }
    printf("Wrote %u bytes into memory\n", size * offset);
}