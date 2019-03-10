#pragma once

#include "../../test.h"
#include <parser/rules/rules.h>

bool test_rule( bool (*read_func)(struct parser *),
                            char *input, char *expected_string);
bool test_not_rule(bool (*read_func)(struct parser *), char *input);
struct ast_node *ast_from_read( bool (*read_func)(struct parser *),
                                char *input);
