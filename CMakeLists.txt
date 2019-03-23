cmake_minimum_required(VERSION 3.9)
project(42sh)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra -pedantic -Werror -g -D_GNU_SOURCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### 42SH EXECUTABLE

include_directories(src)
include_directories(tests)

file(GLOB_RECURSE SRC_FILES  src/*)
add_executable(42sh src/42sh.c)

add_library(42sh_lib SHARED ${SRC_FILES})
target_link_libraries(42sh 42sh_lib -fsanitize=address)

### UNIT TESTS

file(GLOB_RECURSE TEST_FILES tests/*)

add_library(test_42sh SHARED ${SRC_FILES} ${TEST_FILES})
target_link_libraries(test_42sh 42sh_lib)