add_library(cpu_lib cpu.c cpu.h instruction_set.c instruction_set.h)
target_include_directories(cpu_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${LOG_SRC})
link_libraries(cpu_lib LINK_PUBLIC log_lib)