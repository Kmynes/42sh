cmake_minimum_required(VERSION 3.9)
project(42sh)

set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra -pedantic -Werror -g)
#add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### 42SH EXECUTABLE

include_directories(src)

include_directories(tests)

file(GLOB SRC_FILES  
        src/*.c
        src/*/*.c
        src/*/*/*.c
)

add_executable(42sh ${SRC_FILES})

add_library(42sh_lib ${SRC_FILES})


### UNIT TESTS

file(GLOB TEST_FILES
        tests/unit/*.c
        tests/unit/*/*.c
        tests/unit/*/*/*.c
        )

enable_testing()
include_directories(tests tests/unit)
add_executable(test_42sh ${TEST_FILES})

target_link_libraries(test_42sh 42sh_lib -fsanitize=address)

