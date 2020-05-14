add_library(log_lib logger.c logger.h debugger.c debugger.h)
target_include_directories(log_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})