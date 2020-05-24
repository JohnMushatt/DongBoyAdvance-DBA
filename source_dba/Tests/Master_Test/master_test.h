//
// Created by johnm on 5/16/2020.
//
#ifdef _BUILD_WITH_TESTING
#ifndef DONGBOYADVANCE_MASTER_TEST_H
#define DONGBOYADVANCE_MASTER_TEST_H

#include "test_CPU.h"
#include "test_Instructions.h"


/**
 * Master test suite function, calls all sub-tests
 * @todo Allow calling of individual sub-tests
 * @body It will probably be useful later on if individual test and/or test packages
 * can be called instead of calling the master suite
 */
void master_test_suite(void);
void display_results(void);
/**
 * Setup testing variables i.e. passing, failing, overall
 * @todo Setup testing variables i.e. passing, failing, overall
 * @body Testing framework needs some global/status variables that represent how many tests passed/failed,
 * what tests passed/failed, etc.
 * Labels: @Testing
 */
uint64_t total_tests;
uint64_t passed_tests;
uint64_t failed_tests;
#endif //DONGBOYADVANCE_MASTER_TEST_H
#endif //_BUILD_WITH_TESTING