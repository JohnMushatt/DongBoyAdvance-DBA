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
/**
 * Debugging code
 */
#ifdef _DEBUG_MODE
#include "debugger.h"
#endif
int main(int argc, char **argv) {
#ifdef _DEBUG_MODE
    Process_Info *process_info = (Process_Info *) malloc(sizeof(Process_Info));
    process_info->process_id = getpid();

    if (argc > 1) {
        if (strcmp(argv[argc-1], "-d") == 0) {
            debug = true;
        } else {
            debug = false;
        }
    }
    if (debug) {

        begin_debug(process_info);
    }
#endif

    Rom_Info *rom_info = (Rom_Info *) malloc(sizeof(Rom_Info));
    read_rom(rom_info);
    init_cpu();
    Logical_MOV(0, 12);
    Logical_MOV(1, 12);
    Arithmetic_CMP(0, 1, false);
    while (1) {

    }
    return 0;
}
