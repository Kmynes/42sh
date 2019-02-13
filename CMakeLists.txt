cmake_minimum_required(VERSION 3.9)
project(42sh)

set(CMAKE_C_STANDARD 99)

#add_compile_options(-Wall -Wextra -pedantic -Werror)
add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### 42SH EXECUTABLE

include_directories(src)

set(SRC_FILES src/execution/execute_ast.c
        src/execution/execute_ast.h
        src/lexer/lexer.c
        src/lexer/lexer.h
        src/parser/rules/element.c
        src/parser/rules/element.h
        src/parser/parser.c
        src/parser/parser.h
        src/options.c
        src/options.h
        src/42sh.c)

add_executable(42sh ${SRC_FILES})

add_library(42sh_lib ${SRC_FILES})


### UNIT TESTS

enable_testing()
include_directories(tests tests/unit)
add_executable(test_42sh tests/unit/main.c tests/unit/parser/test_parser.c)
target_link_libraries(test_42sh 42sh_lib)

