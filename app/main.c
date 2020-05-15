//
// Created by johnm on 5/14/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    printf("Launching cygserver from C:\\cygwin64\\usr\\sbin\\cygserver.exe for shared memory between DBA and the dugger!\n");
    char *cygserver_args[4];
    cygserver_args[0] = "run";
    cygserver_args[1] = "mintty";
    cygserver_args[2] = "/usr/sbin/cygserver.exe";
    cygserver_args[3] = NULL;
    pid_t fd = fork();
    if (fd == 0) {
        execvp(cygserver_args[0], cygserver_args);
    }
    printf("Successfully starter cygserver!\n");
    return 0;
}