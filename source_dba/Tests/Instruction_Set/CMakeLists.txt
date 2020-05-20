add_library(Test_Instructions test_Instructions.c test_Instructions.h)
target_include_directories(Test_Instructions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CPU_SRC} )
link_libraries(Test_Instructions LINK_PUBLIC cpu_lib)
