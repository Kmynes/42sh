#include "unit/parser/rules/test_rules.h"

void test_read_command_simple_command(void)
{
    bool check1 = test_rule(read_command, "toto", "AST_COMMAND(1)");
    struct ast_node *ast = ast_from_read(read_command, "toto");
    bool check2 = ast->children[0]->type == AST_SIMPLE_COMMAND;
    print_state_test(check1 && check2, "test_read_command_simple_command");

    ast_free(ast);
}

void test_read_command_fail(void)
{
    bool check = test_not_rule(read_command, "for toto");
    print_state_test(check, "test_read_command_fail");
}

void test_read_command(void)
{
    test_read_command_simple_command();
    test_read_command_fail();
}