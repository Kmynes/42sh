#include "helper_rules.h"

bool test_rule(bool (*read_func)(struct parser *),
    char *input, char *expected_string)
{
    struct parser *p = parser_new_from_string(input);
    if (!read_func(p))
    {
        printf("test_rule, for expected : %s, read function returned false\n", 
            expected_string);
        parser_free(p);
        return false;
    }

    bool res = true;
    struct ast_node *ast = p->ast->children[0];
    if (expected_string)
    {
        char *s = ast->to_string(ast);
        res = strcmp(s, expected_string) == 0;
        if (!res)
            printf("test_rule '%s' didn't match expected '%s'\n", s,
                expected_string);
        free(s);
    }
    parser_free(p);
    return res;
}

bool test_not_rule( bool (*read_func)(struct parser *), char *input)
{
    struct parser *p = parser_new_from_string(input);
    bool res = !read_func(p);
    parser_free(p);

    return res;
}

struct ast_node *ast_from_read( bool (*read_func)(struct parser *),
                                char *input)
{
    struct parser *p = parser_new_from_string(input);
    if (!read_func(p))
    {
        printf("test_rule, for input : %s, read function returned false\n",
            input);
        parser_free(p);
        return NULL;
    }

    struct ast_node *ast = p->ast->children[0];
    parser_free_no_ast(p);
    return ast;
}