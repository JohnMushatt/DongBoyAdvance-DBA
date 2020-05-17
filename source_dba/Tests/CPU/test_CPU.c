//
// Created by johnm on 5/16/2020.
#ifdef _BUILD_WITH_TESTING

#include "test_CPU.h"
void test_cpu_master() {
    test_cpu_cpsr();
}
void test_cpu_cpsr() {
    cpsr.Mode_bits = 0x3;
    if (cpsr.status != 0x3) {
        Error_Message err = {"cpsr bits not set correctly", 0x100};
        log_err(err);
    }
    cpsr.N_Sign_flag = 1;
    if (cpsr.status >> 31 != 1) {
        Error_Message err = {"cpsr bits not set correctly", 0x100};
        log_err(err);
    }
}
#endif //_BUILD_WITH_TESTING
