#include "test_options.h"

void test_version(void)
{
    char **input = malloc(100);
    input[1] = "--version";
    int argc = 2;
    assert(options_parser(input, argc) == 0);
}

void test_invalid(void)
{
    char **input = malloc(100);
    input[1] = "--vern";
    int argc = 2;
    assert(options_parser(input, argc) == 1);
}

void test_suite_options(void)
{
    test_version();
    test_invalid();
}