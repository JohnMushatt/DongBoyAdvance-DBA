//
// Created by johnm on 5/16/2020.
//

#ifdef _BUILD_WITH_TESTING
#include "master_test.h"
void master_test_suite(void) {
    test_cpu_master();
    test_instruction_master();
    display_results();
}

void display_results(void) {
    printf("Total tests run: %lu%16s: %lu%16s: %lu\n",total_tests,"passed tests",passed_tests,"failed tests",failed_tests);
}
#endif // _BUILD_WITH_TESTING
