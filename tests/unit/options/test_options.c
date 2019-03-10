#include "test_options.h"

void test_version(void)
// Tests that --version command works
{
    char **input = malloc(100);
    input[1] = "--version";
    int argc = 2;
    assert(options_parser(input, argc) == 0);
    free(input);
}

void test_invalid(void)
// Tests that there are no errors when bad input is given
{
    char **input = malloc(100);
    input[1] = "--vern";
    int argc = 2;
    assert(options_parser(input, argc) == 1);
    free(input);
}

void test_command_input(void)
/* this test checks that there are no segfaults when giving normal
** input. this might be an issue later on when coomands are supported.
*/
{
    char **input = malloc(100);
    int argc = 3;
    input[1] = "-c";
    input[2] = "find;";
    assert(options_parser(input, argc) == 1);
    free(input);
}

void test_no_input(void)
/* this test checks that there are no segfaults when giving normal
** input. this might be an issue later on when coomands are supported.
*/
{
    char **input = NULL;
    int argc = 1;
    assert(options_parser(input, argc) == 0);
}

void test_suite_options(void)
{
    test_version();
    test_invalid();
    test_command_input();
    test_no_input();
}