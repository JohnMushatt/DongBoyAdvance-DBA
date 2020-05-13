add_library(log_lib logger.c logger.h)
target_include_directories(log_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})