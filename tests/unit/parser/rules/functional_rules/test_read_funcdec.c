#include "unit/parser/rules/test_rules.h"

static void test_read_funcdec_simple(void)
{
    char *input = "function toto()\n\n{echo toto}";
    assert(test_rule(read_funcdec, input, "AST_FUNCDEC(1)"));
    struct ast_node *ast = ast_from_read(read_funcdec, input);
    assert(ast->children[0]->type == AST_SHELL_COMMAND);
    ast_free(ast);
}

static void test_read_funcdec_simple2(void)
{
    char *input = "function toto()\n\n(echo toto)";
    assert(test_rule(read_funcdec, input, "AST_FUNCDEC(1)"));
    struct ast_node *ast = ast_from_read(read_funcdec, input);
    assert(ast->children[0]->type == AST_SHELL_COMMAND);
    ast_free(ast);
}

void test_read_funcdec_fail(void)
{
    assert(test_not_rule(read_funcdec, "function"));
}

void test_read_funcdec(void)
{
    test_read_funcdec_simple();
    test_read_funcdec_simple2();
    test_read_funcdec_fail();
}