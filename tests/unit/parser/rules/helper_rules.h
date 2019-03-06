#pragma once

#include "../../test.h"
#include <parser/rules/rules.h>

void test_rule(bool (*read_func)(struct parser *),
    char *input, char *expected_string);
void test_rule_capture(bool (*read_func)(), char *input,
    char *expected_string);
void test_not_rule(bool (*read_func)(struct parser *), char *input);
