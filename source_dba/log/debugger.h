//
// Created by johnm on 5/13/2020.
//
#ifdef _DEBUG_MODE
#ifndef DONGBOYADVANCE_DEBUGGER_H
#define DONGBOYADVANCE_DEBUGGER_H


#ifdef __unix__
#define LINUX_MODE

#elif defined(WIN64) || defined(_WIN32)
#define WINDOWS_MODE
#include <windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

key_t key;
typedef struct _process_info {
    pid_t process_id;
    pid_t debug_id;
} Process_Info;

void *begin_debug(void *arg);
void IPC_mmap(void);

void init_shared_mem(void);

#endif //DONGBOYADVANCE_DEBUGGER_H
#endif