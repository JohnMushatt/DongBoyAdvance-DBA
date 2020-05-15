//
// Created by johnm on 5/13/2020.
//
#ifdef _DEBUG_MODE

#include "debugger.h"

#ifdef _CYGWIN

void start_cygserver() {
    /*
    printf("Launching cygserver from C:\\cygwin64\\usr\\sbin\\cygserver.exe for shared memory between DBA and the dugger!\n");
    char *cygserver_args[4];
    cygserver_args[0] = "run";
    cygserver_args[1] = "mintty";
    //cygserver_args[2] = "C:\\cygwin64\\Cygwin.bat";
    cygserver_args[2] = "/usr/sbin/cygserver.exe";
    cygserver_args[3] = NULL;
    pid_t fd = fork();
    if (fd == 0) {
        execvp(cygserver_args[0], cygserver_args);
    }

    cygserver_args[0] = "run";
    cygserver_args[1] = "mintty";
    //cygserver_args[2] = "C:\\cygwin64\\Cygwin.bat";
    cygserver_args[2] = "/usr/sbin/cygserver.exe";
    cygserver_args[3] = NULL;
    fd = fork();
    if (fd == 0) {
        execvp(cygserver_args[0], cygserver_args);
    }
     */



    /**
     * Attempt to generate a unique shm key for IPC via shared memory access
     */
    int shmid;
    // key = 1234;//ftok("C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\shared_memory\\shmfile", 65);
    if ((shmid = shmget(1, 1024, IPC_CREAT | 0666)) == -1) {

        perror("shmget");
        // printf(perr)
        exit(1);
    }
    char *shmaddr = (char *) shmat(shmid, (void *) 0, 0);

    printf("Shared memory starts at %p\n", shmaddr);
    sprintf(shmaddr, "Hi there");
}

#endif


void begin_debug(Process_Info *arg) {

#ifdef WINDOWS_MODE
    printf("WINDOWS MODE\n");

    FreeConsole();
    AttachConsole(process_info->process_id);
#endif
#ifdef LINUX_MODE

    char *cmd = "run";
    char *args[4];
    args[0] = "run";
    args[1] = "mintty";
    args[3] = NULL;
    args[2] = malloc(sizeof(char) * 128);
    snprintf(args[2], 128,
             "C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\DongBoyAdvance_Debugger\\cmake-build-debug\\DongBoyAdvance_debugger_v1.0.0.exe"/*, arg->process_id*/);
    pid_t id = fork();
    if (id == 0) {
        execvp(args[0], args);
    } else {
        arg->debug_id = id;
    }
#endif
}

#endif