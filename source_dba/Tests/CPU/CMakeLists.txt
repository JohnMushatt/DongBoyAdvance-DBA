add_library(Test_CPU test_CPU.c test_CPU.h)
target_include_directories(Test_CPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CPU_SRC} )
link_libraries(Test_CPU LINK_PUBLIC cpu_lib)
