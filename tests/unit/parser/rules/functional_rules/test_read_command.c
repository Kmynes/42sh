#include "unit/parser/rules/test_rules.h"

void test_read_command_simple_command(void)
{
    test_rule(read_command, "toto", "AST_COMMAND(1)");
    struct ast_node *ast = ast_from_read(read_command, "toto");
    assert(ast->children[0]->type == AST_SIMPLE_COMMAND);
    ast_free(ast);
}

void test_read_command_fail(void)
{
    test_not_rule(read_command, " toto");
}

void test_read_command(void)
{
    test_read_command_simple_command();
    test_read_command_fail();
}