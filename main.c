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

#include "Master_Test/master_test.h"

#endif
/**
 * Debugging code
 */
#ifdef _DEBUG_MODE

#include "debugger.h"
//#include "cpu
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

    Rom_Info *rom_info = (Rom_Info *) malloc(sizeof(Rom_Info));
    // read_rom(rom_info);
    init_cpu();

    while (1) {

    }
    return 0;
}
