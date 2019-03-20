#include "test_utils.h"
#include <utils/string.h>

static void test_str_replace(void)
{
    char *str = strdup("${part1} ${part2} $part3");
    str = str_replace("${part1}", "project", str);
    str = str_replace("${part2}", "42", str);
    str = str_replace(" $part3", "sh", str);
    bool check = strcmp(str, "project 42sh") == 0;
    print_state_test(check, "test_str_replace");
    free(str);
}

void test_string(void)
{
    test_str_replace();
}