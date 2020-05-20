//
// Created by johnm on 5/10/2020.
//

#ifndef DONGBOYADVANCE_LOGGER_H
#define DONGBOYADVANCE_LOGGER_H

#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cpu.h>
#include <unistd.h>

/**
 * Error struct
 */
typedef struct _error_message {
    char *error_msg;
    int32_t code;
} Error_Message;

/**
 * General Message struct
 */
typedef struct _general_message {
    char *log;
    int32_t code;
    char *instruction_name;
} General_Message;

/**
 * Test logging function
 */
void logger(const char *tag, const char *message);

/**
 * CPU initialization logging function
 */
void cpu_init_log();

void print_gen_reg();

void print_cond_flag();

void print_cpsr();

void log_err(Error_Message err);

void log_msg(General_Message msg);

void print_stack_pointer();

void print_program_counter();

void print_link_register();

#endif //DONGBOYADVANCE_LOGGER_H
