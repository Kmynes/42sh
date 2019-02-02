cmake_minimum_required(VERSION 3.0)
project(42sh)

set(CMAKE_C_STANDARD 99)
#set(GCC_COVERAGE_COMPILE_FLAGS "")

add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(.)
include_directories(tests)

add_executable(42sh
        src/src.c)
