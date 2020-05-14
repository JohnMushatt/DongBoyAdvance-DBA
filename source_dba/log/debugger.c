//
// Created by johnm on 5/13/2020.
//

#include "debugger.h"
void *begin_debug(void *arg) {
    Process_Info *process_info = (Process_Info *) arg;
#ifdef WINDOWS_MODE
    printf("WINDOWS MODE\n");

    FreeConsole();
    AttachConsole(process_info->process_id);
#endif
#ifdef LINUX_MODE
    char command[128];
    memset(&command,0,128);
    snprintf(command,128,"run mintty 'gdb DongBoyAdvance_v1.0.0.exe attach %d'",process_info->process_id);
    printf("%s\n",command);
    system(command);
#endif
    return 0;
}