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
        return 0;
    }
    else
    {
        return 1;
    }
}