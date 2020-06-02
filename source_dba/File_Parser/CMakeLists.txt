add_library(File_lib rom_parser.c rom_parser.h)
target_include_directories(File_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})