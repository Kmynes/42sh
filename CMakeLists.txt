cmake_minimum_required(VERSION 3.12)
project(42sh)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### 42SH EXECUTABLE

include_directories(src)
include_directories(src/parser)

add_executable(42sh
        src/parser/rules/element.c
        src/parser/rules/element.h
        src/parser/parser.c
        src/parser/parser.h
        src/42sh.c)

add_library(42sh_lib src/parser/rules/element.c
        src/parser/rules/element.h
        src/parser/parser.c
        src/parser/parser.h
        src/42sh.c)


### UNIT TESTS

enable_testing()
find_package(Check REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(tests)
include_directories(tests/unit)
add_executable(test_42sh tests/unit/main.c tests/unit/parser/test_parser.c)
target_link_libraries(test_42sh 42sh_lib Threads::Threads ${CHECK_LIBRARIES})

