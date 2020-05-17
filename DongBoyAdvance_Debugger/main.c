//
// Created by johnm on 5/14/2020.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int32_t id;
    printf("Running DongBoyAdvance Debugger!\n");
    key_t key = ftok("C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\shared_memory\\shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *current_string = (char *) shmat(shmid, (void *) 0, 0);
    char *prev_string = (char *) malloc(sizeof(char) * 1024);
    while (strcmp(current_string, prev_string) != 0) {
        printf("%s\n", current_string);
        strcpy(prev_string, current_string);
    }
    //scanf("%d",&id);
    *current_string='*';
    sprintf(current_string,"print var MEMORY");
    return 0;
}