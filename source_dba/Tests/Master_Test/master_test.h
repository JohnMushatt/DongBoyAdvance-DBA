//
// Created by johnm on 5/16/2020.
//
#ifdef _BUILD_WITH_TESTING
#ifndef DONGBOYADVANCE_MASTER_TEST_H
#define DONGBOYADVANCE_MASTER_TEST_H
/**
 * @todo Fix this include issue
 * @body For some reason this thing just isn't working with CMake
 */
//#include "test_CPU.h"
/**
 * Master test suite function, calls all sub-tests
 * @todo Allow calling of individual sub-tests
 * @body It will probably be useful later on if individual test and/or test packages
 * can be called instead of calling the master suite
 */
void master_test_suite(void);
#endif //DONGBOYADVANCE_MASTER_TEST_H
#endif //_BUILD_WITH_TESTING