#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "utils/test_utils.h"
#include "helper_unit.h"

int test_unit(void)
{
    test_suite_parser();
    test_execution();
    test_ast_print();
    test_utils();

    if (global_condition)
    {
        printf("\n\033[1;32mUNIT TESTS : PASSED\033[0m\n");
        return 0;
    }
    else
    {
        printf("\n\033[31mUNIT TESTS : FAILED\033[0m\n");
        return 1;
    }
}