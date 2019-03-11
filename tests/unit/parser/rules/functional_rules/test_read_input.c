#include "unit/parser/rules/test_rules.h"

void test_read_input_eof(void)
{
    char *input = "";
    test_rule(read_input, input, "AST_INPUT(0)");
}

void test_read_input_new_line(void)
{
    char *input = "\n";
    assert(test_rule(read_input, input, "AST_INPUT(0)"));
    struct ast_node *ast = ast_from_read(read_input, input);

    ast_free(ast);
}


void test_read_input_simple(void)
{
    char *input = "toto;\n";
    assert(test_rule(read_input, input, "AST_INPUT(1)"));
    struct ast_node *ast = ast_from_read(read_input, input);
    assert(ast->children[0]->type == AST_LIST);

    ast_free(ast);
}

void test_read_input_simple2(void)
{
    char *input = "toto;";
    assert(test_rule(read_input, input, "AST_INPUT(1)"));
    struct ast_node *ast = ast_from_read(read_input, input);
    assert(ast->children[0]->type == AST_LIST);

    ast_free(ast);
}


void test_read_input_fail(void)
{
    char *input = "toto;tit\n";
    assert(test_not_rule(read_input, input));
}

void test_read_input(void)
{
    test_read_input_new_line();
    test_read_input_eof();
    test_read_input_simple();
    test_read_input_simple2();
    test_read_input_fail();
}