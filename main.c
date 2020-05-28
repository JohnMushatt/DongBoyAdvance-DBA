//
// Created by johnm on 5/10/2020.
//
#include "cpu.h"
#include "instruction_set.h"
#include "string.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "rom_parser.h"

#ifdef _BUILD_WITH_TESTING

#include "master_test.h"

#endif
/**
 * Debugging code
 */
#ifdef _DEBUG_MODE

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

#include "debugger.h"
#endif

int main(int argc, char **argv) {


#ifdef _BUILD_WITH_TESTING

    master_test_suite();
#endif


#ifdef _DEBUG_MODE
    Process_Info *process_info = (Process_Info *) malloc(sizeof(Process_Info));
    process_info->process_id = getpid();
    pthread_t pid;


    pthread_create(&pid, NULL, &begin_debug, (void *) process_info);

#endif

    read_rom();
    init_cpu();
    ARM_U_WORD opcode;
    while (rom_info->current_opcode < rom_info->rom_size) {
        opcode = fetch_opcode();
        print_binary(opcode);
        decode(opcode);
    }
    destroy_rom();

    return 0;
}
