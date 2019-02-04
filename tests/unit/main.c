#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main(void)
{
    struct Suite *s = suite_create("unit_tests");

    test_parser(s);

    struct SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);

    return 0;
}
