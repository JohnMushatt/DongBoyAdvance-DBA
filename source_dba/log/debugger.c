//
// Created by johnm on 5/13/2020.
//
#ifdef _DEBUG_MODE

#include "debugger.h"

/**
 * Attach to shared memory region
 * TODO: Add this function to work in a thread to handle background interaction
 */
void init_shared_mem() {


    /**
     * Attempt to generate a unique shm key for IPC via shared memory access
     */
    int shmid;
    key = ftok("C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\shared_memory\\shmfile", 65);
    if ((shmid = shmget(key, 1024, IPC_CREAT | 0666)) == -1) {

        perror("shmget");
        // printf(perr)
        exit(1);
    }
    char *shmaddr = (char *) shmat(shmid, (void *) 0, 0);

    printf("Shared memory starts at %p\n", shmaddr);
    sprintf(shmaddr, "Hi there");
    while (*shmaddr != '*') {
        sleep(1);
    }
    printf("Current debugger command: %s\n",shmaddr);
}


void *begin_debug(void *arg) {
    Process_Info *process_info = (Process_Info *) arg;
#ifdef WINDOWS_MODE
    printf("WINDOWS MODE\n");

    FreeConsole();
    AttachConsole(process_info->process_id);
#endif
#ifdef LINUX_MODE
    init_shared_mem();

#endif
}

#endif