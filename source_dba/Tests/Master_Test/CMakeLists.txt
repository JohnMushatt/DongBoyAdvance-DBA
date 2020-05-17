add_library(Test_Master master_test.c master_test.h)
target_include_directories(Test_Master PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${TEST_CPU_SRC})
#target_include_directories(Test_Master PUBLIC ${TEST_CPU_SRC})
link_libraries(Test_Master LINK_PUBLIC Test_CPU)

