cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(DongBoyAdvance_debugger VERSION 1.0.0 LANGUAGES C)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/DongBoyAdvance_Debugger)
set(HELP_MSG "Email john.mushatt@gmail.com and hope he can fix it")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")


set(EXE_NAME ${PROJECT_NAME}_v${PROJECT_VERSION})
set(CMAKE_C_STANDARD  11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Werror -lpthread -lncurses")

file(GLOB_RECURSE DBA_DEBUGGER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/source*.c")
file(GLOB_RECURSE DBA_DEBUGGER_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/source*.h")

set (DBA_DEBUGGER_INCLUDE_DIRS "")
foreach (_headerFile ${DBA_DEBUGGER_HEADER})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND DBA_DEBUGGER_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES DBA_DEBUGGER_INCLUDE_DIRS)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${EXE_NAME} main.c ${DBA_DEBUGGER_SRC} main.c)
#target_include_directories(${EXE_NAME} PRIVATE ${LOG_SRC} ${CPU_SRC})

target_link_libraries(${EXE_NAME} ${CURSES_LIBRARIES})
