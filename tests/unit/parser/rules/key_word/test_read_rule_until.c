#include "unit/parser/rules/test_rules.h"

void test_read_rule_until_simple(void)
{
    char *input = "until\n\necho hello\ndo\nls\ndone";
    bool check = test_rule(read_rule_until, input, "AST_RULE_UNTIL(2)");
    print_state_test(check, "test_read_rule_until_simple (1)");

    struct ast_node *ast = ast_from_read(read_rule_until, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_rule_until_simple (2)");

    check = ast->children[1]->type == AST_DO_GROUP;
    print_state_test(check, "test_read_rule_until_simple (3)");
    ast_free(ast);
}

void test_read_rule_until_complex(void)
{
    char *input = "until\n\necho toto;\necho titi\necho"
                  "tutu\ndo\nls;cat;find;\ndone";
    bool check = test_rule(read_rule_until, input, "AST_RULE_UNTIL(2)");
    print_state_test(check, "test_read_rule_until_complex (1)");

    struct ast_node *ast = ast_from_read(read_rule_until, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_rule_until_complex (2)");
    check = ast->children[1]->type == AST_DO_GROUP;
    print_state_test(check, "test_read_rule_until_complex (3)");
    ast_free(ast);
}

void test_read_rule_until_fail(void)
{
    char *input = "echo toto";
    bool check = test_not_rule(read_rule_until, input);
    print_state_test(check, "test_read_rule_until_fail");
}

void test_read_rule_until(void)
{
    test_read_rule_until_simple();
    test_read_rule_until_complex();
    test_read_rule_until_fail();
}