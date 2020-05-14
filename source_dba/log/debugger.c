//
// Created by johnm on 5/13/2020.
//
#ifdef _DEBUG_MODE
#include "debugger.h"

void begin_debug(Process_Info *arg) {

#ifdef WINDOWS_MODE
    printf("WINDOWS MODE\n");

    FreeConsole();
    AttachConsole(process_info->process_id);
#endif
#ifdef LINUX_MODE

    //pthread_create(&thread_id, NULL, &begin_debug, (void*) process_info);
    char *cmd = "run";
    char *args[4];
    args[0] = "run";
    args[1] = "mintty";
    args[3] = NULL;
    args[2] = malloc(sizeof(char)*128);
    snprintf(args[2], 128, "C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\DongBoyAdvance_Debugger\\cmake-build-debug\\DongBoyAdvance_debugger_v1.0.0.exe"/*, arg->process_id*/);
    pid_t id = fork();
    if (id==0) {
        execvp(args[0],args);
    }
    else {
        arg->debug_id = id;
    }
#endif
}

#endif