//
// Created by johnm on 5/10/2020.
//
#include "cpu.h"
#include "instruction_set.h"
#include "string.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "debugger.h"
#include <stdlib.h>
int main(int argc, char **argv) {
    Process_Info *process_info = (Process_Info *)  malloc(sizeof(Process_Info));
    process_info->process_id= getpid();
    pthread_t thread_id;
    if(argc>1) {
        if(strcmp(argv[1],"-d")==0) {
            debug=true;
        }
        else {
            debug=false;
        }
    }
    if(debug) {
        pthread_create(&thread_id, NULL, &begin_debug, (void*) process_info);

    }
    init_cpu();
    Logical_MOV(0,12);
    Logical_MOV(1,12);
    Arithmetic_CMP(0,1,false);
    while(1) {

    }
    return 0;
}
