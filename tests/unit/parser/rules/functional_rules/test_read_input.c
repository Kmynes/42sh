#include "unit/parser/rules/test_rules.h"

void test_read_input_simple(void)
{
    char *input = "toto;\n";
    assert(test_rule(read_input, input, "AST_INPUT(1)"));
    struct ast_node *ast = ast_from_read(read_input, input);
    assert(ast->children[0]->type == AST_LIST);

    ast->exec(ast);
    ast_free(ast);
}


void test_read_input(void)
{
    test_read_input_simple();
}