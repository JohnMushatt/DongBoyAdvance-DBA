cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(DongBoyAdvance VERSION 1.0.2 LANGUAGES C)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source_dba)
set(HELP_MSG "Email john.mushatt@gmail.com and hope he can fix it")

#Set cpu source
set(CPU_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CPU)
#Set log source
set(LOG_SRC ${CMAKE_CURRENT_SOURCE_DIR}/log)
#Set File parsing source
set(FILE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/File_Parser)
#Set Test source
set(TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
set(TEST_CPU_SRC ${TEST_SRC}/CPU)
set(TEST_INSTRUCTION_SRC ${TEST_SRC}/Instruction_Set)
set(TEST_MASTER_SRC ${TEST_SRC}/Master_Test)
set(EXE_NAME ${PROJECT_NAME}_v${PROJECT_VERSION})
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Werror -lpthread -lncurses --coverage")

file(GLOB_RECURSE DBA_SRC "source_dba/*.c")
file(GLOB_RECURSE DBA_HEADER "source_dba/*.h")

set(DBA_INCLUDE_DIRS "")
foreach (_headerFile ${DBA_HEADER})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND DBA_INCLUDE_DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES DBA_INCLUDE_DIRS)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

if (${CMAKE_BUILD_TYPE} MATCHES "DEBUG")
    #ADD_DEFINITIONS(-D_DEBUG_MODE)
    message(STATUS "Debug Mode")
else ()
    message(STATUS "Release Mode")
endif ()
if (${CYGWIN})
    message(STATUS "Cygwin found, setting definition to start cygserver!")
    ADD_DEFINITIONS(-D_CYGWIN)
else ()
    message(STATUS "Cygwin not found!")

endif ()
set(TEST_MODE FALSE)
set(LOG_MODE TRUE)
if (${TEST_MODE})
    message(STATUS "Building with tests")
    ADD_DEFINITIONS(-D_BUILD_WITH_TESTING)
else ()
    message(STATUS "Building without tests")
endif ()

if (${LOG_MODE})
    message(STATUS "Building with logging")
    ADD_DEFINITIONS(-D_BUILD_WITH_LOGGING)
else ()
    message(STATUS "Building without logging")
endif ()
add_executable(${EXE_NAME} main.c ${DBA_SRC})
target_include_directories(${EXE_NAME} PRIVATE ${LOG_SRC} ${CPU_SRC} ${FILE_SRC} ${TEST_MASTER_SRC} ${TEST_CPU_SRC} ${TEST_INSTRUCTION_SRC})

target_link_libraries(${EXE_NAME})
