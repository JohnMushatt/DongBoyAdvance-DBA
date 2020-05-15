//
// Created by johnm on 5/14/2020.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main() {
    int32_t id;
    printf("Running DongBoyAdvance Debugger!\n");
    key_t  key =ftok("C:\\Users\\johnm\\Desktop\\DongBoyAdvance-DBA\\shared_memory\\shmfile",65);
    int shmid = shmget(key,1024,0666 | IPC_CREAT);
    char *str = (char *) shmat(shmid, (void *)0,0);
    printf("Data read from main program: %s\n",str);
    //scanf("%d",&id);
    return 0;
}