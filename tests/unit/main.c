#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main(void)
{
    test_suite_parser();
    test_suite_options();
    printf("\nUNIT TESTS : PASSED\n");

    return 0;
}