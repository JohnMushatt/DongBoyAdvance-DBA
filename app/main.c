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
    //cygserver_args[2] = "C:\\cygwin64\\Cygwin.bat";
    cygserver_args[2] = "/usr/sbin/cygserver.exe";
    cygserver_args[3] = NULL;
    pid_t fd = fork();
    if (fd == 0) {
        execvp(cygserver_args[0], cygserver_args);
    }
    char *dba_args[4];
    dba_args[0] = "run";
    dba_args[1] = "mintty";
    dba_args[2] = "C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\cmake-build-debug\\DongBoyAdvance_v1.0.0.exe -d";
    dba_args[3] = NULL;
    fd = fork();
    if (fd == 0) {
        execvp(dba_args[0], dba_args);
    }
}