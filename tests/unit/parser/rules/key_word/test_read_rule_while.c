#include "unit/parser/rules/test_rules.h"

void test_read_rule_while_simple(void)
{
    char *input = "while\n\ni=2\ndo\nls\ndone";
    bool check = test_rule(read_rule_while, input, "AST_RULE_WHILE(2)");
    print_state_test(check, "test_read_rule_while_simple (1)");

    struct ast_node *ast = ast_from_read(read_rule_while, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_rule_while_simple (2)");

    check = ast->children[1]->type == AST_DO_GROUP;
    print_state_test(check, "test_read_rule_while_simple (3)");
    ast_free(ast);
}

void test_read_rule_while_complex(void)
{
    char *input = "while\n\necho toto;\necho titi\necho tutu\n"
                  "do\nls;cat;find;\ndone";
    bool check = test_rule(read_rule_while, input, "AST_RULE_WHILE(2)");
    print_state_test(check, "test_read_rule_while_complex (1)");
    struct ast_node *ast = ast_from_read(read_rule_while, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_rule_while_complex (2)");

    check = ast->children[1]->type == AST_DO_GROUP;
    print_state_test(check, "test_read_rule_while_complex (3)");
    ast_free(ast);
}

void test_read_rule_while_fail(void)
{
    char *input = "echo toto";
    bool check = test_not_rule(read_rule_while, input);
    print_state_test(check, "test_read_rule_while_fail");
}

void test_read_rule_while(void)
{
    test_read_rule_while_simple();
    test_read_rule_while_complex();
    test_read_rule_while_fail();
}