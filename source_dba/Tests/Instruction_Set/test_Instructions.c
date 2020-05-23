//
// Created by johnm on 5/20/2020.
//
#ifdef _BUILD_WITH_TESTING
#include <master_test.h>
#include "test_Instructions.h"

void test_instruction_master(void) {
    test_Arithmetic();
}
void test_Arithmetic(void) {
    test_AND_Immediate();
    test_AND_Register();
    test_AND_Shift();
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

/**
 * Test AND instruciton between reg_1 - > MEMORY[0] & reg_2 -> array[4]
 */
void test_AND_Shift(void){
    zero_reg(3,0,1,2);
    set_memory_range_random(0,0xf,WORD);
    set_reg(1,4);
    set_reg(2,8);
    Arithmetic_AND_Register_Shifted(0,1,2,1);
    total_tests++;
    if(gpr.registers[0].data != (gpr.registers[1].data & get_word(gpr.registers[2].data+sizeof(ARM_U_WORD)*1))) {
        failed_tests++;
    }
    else {
        passed_tests++;
    }
}
#endif //_BUILD_WITH_TESTING