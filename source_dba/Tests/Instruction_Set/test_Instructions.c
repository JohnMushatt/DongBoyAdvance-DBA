//
// Created by johnm on 5/20/2020.
//

#include <master_test.h>
#include "test_Instructions.h"

void test_instruction_master(void) {
    test_Arithmetic();
}
void test_Arithmetic(void) {
    test_AND_Immediate();
    test_AND_Register();
}
void test_AND_Immediate(void) {
    gpr.registers[0].data = 0b0;
    gpr.registers[1].data = 0b1010;
    ARM_U_WORD test = 0b1010;
    Arithmetic_AND_Immediate(0,1,test);
    total_tests++;
    if(gpr.registers[0].data !=0b1010) {
        failed_tests++;
    }
    else {
        passed_tests++;
    }
}
void  test_AND_Register(void) {
    gpr.registers[0].data = 0b0;
    gpr.registers[1].data = 0b1010;
    gpr.registers[2].data = 0b1010;

    Arithmetic_AND_Register(0,1,2);
    total_tests++;
    if(gpr.registers[0].data !=0b1010) {
        failed_tests++;
    }
    else {
        passed_tests++;
    }
}