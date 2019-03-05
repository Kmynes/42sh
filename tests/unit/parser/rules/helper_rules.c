#include "helper_rules.h"

void test_rule( bool (*read_func)(struct parser *), char *input, char *expected_string)
{
    struct parser *p = parser_new_from_string(input);
    assert(read_func(p));

    if (expected_string)
    {
        struct ast_node *ast = p->ast->children[0];
        char *s = ast->to_string(ast);
        assert(strcmp(s, expected_string) == 0);
        free(s);
    }
    parser_free(p);
}

void test_rule_capture( bool (*read_func)(), char *input, char *expected_string)
{
    struct parser *p = parser_new_from_string(input);
    parser_begin_capture(p, "test_rule");
    assert(read_func(p));
    parser_end_capture(p, "test_rule");
    char *s = parser_get_capture(p, "test_rule");

    assert(p->cursor == strlen(expected_string));
    assert(strcmp(s, expected_string) == 0);
    free(s);
    parser_free(p);
}

void test_not_rule( bool (*read_func)(struct parser *), char *input)
{
    struct parser *p = parser_new_from_string(input);
    assert(!read_func(p));
    assert(p->cursor == 0);
    parser_free(p);
}