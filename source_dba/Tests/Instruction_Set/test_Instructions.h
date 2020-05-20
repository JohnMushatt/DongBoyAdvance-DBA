//
// Created by johnm on 5/20/2020.
//
#ifdef _BUILD_WITH_TESTING
#ifndef DONGBOYADVANCE_TEST_INSTRUCTIONS_H
#define DONGBOYADVANCE_TEST_INSTRUCTIONS_H

#include "instruction_set.h"

void test_instruction_master(void);
void test_AND_Immediate(void);
void test_AND_Register(void);
void test_AND_Shift(void);


void test_OR(void);
void test_CMP(void);
void test_ADD(void);
void test_Arithmetic(void);
void test_Logical(void);
void test_Jump(void);
void test_Branch(void);
#endif //DONGBOYADVANCE_TEST_INSTRUCTIONS_H
#endif
