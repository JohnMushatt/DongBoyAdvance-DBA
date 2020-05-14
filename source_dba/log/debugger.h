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
typedef struct _process_info {
    pid_t process_id;
    pid_t debug_id;
} Process_Info;

void begin_debug(Process_Info *arg);

#endif //DONGBOYADVANCE_DEBUGGER_H
#endif