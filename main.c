//
// Created by johnm on 5/10/2020.
//
#include "cpu.h"
#include "instruction_set.h"
#include "string.h"
int main(int argc, char **argv) {

    if(argc>1) {
        if(strcmp(argv[1],"-d")==0) {
            debug=true;
        }
        else {
            debug=false;
        }
    }
    init_cpu();
    Logical_MOV(0,12);
    Logical_MOV(1,12);
    Arithmetic_CMP(0,1,false);
    while(1) {

    }
    return 0;
}
