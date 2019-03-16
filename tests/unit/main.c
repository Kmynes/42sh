#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main(void)
{
    test_suite_parser();
    test_execution();
    test_ast_print();
    printf("\n\033[1;32mUNIT TESTS : PASSED\033[1;0m\n");

    return 0;
}