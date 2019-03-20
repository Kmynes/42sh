#include "unit/parser/rules/test_rules.h"

void test_read_do_group_simple(void)
{
    char *input = "do\nls\ndone";
    bool check = test_rule(read_do_group, input, "AST_DO_GROUP(1)");
    print_state_test(check, "test_read_do_group_simple (1)");

    struct ast_node *ast = ast_from_read(read_do_group, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_do_group_simple (2)");
    ast_free(ast);
}

void test_read_do_group_simple_2(void)
{
    char *input = "do\ntutu&&titi;tata||toto\ndone";
    bool check = test_rule(read_do_group, input, "AST_DO_GROUP(1)");
    print_state_test(check, "test_read_do_group_simple_2 (1)");

    struct ast_node *ast = ast_from_read(read_do_group, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_do_group_simple_2 (2)");
    ast_free(ast);
}

void test_read_do_group_fail(void)
{
    char *input = "do\n\ndone";
    bool check = test_not_rule(read_do_group, input);
    print_state_test(check, "test_read_do_group_fail");
}

void test_read_do_group(void)
{
    test_read_do_group_simple();
    test_read_do_group_simple_2();
    test_read_do_group_fail();
}