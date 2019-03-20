#include "unit/parser/rules/test_rules.h"

void test_read_rule_case_simple(void)
{
    char *input = "case var in\ncase1)\nstart\n;;esac";
    bool check = test_rule(read_rule_case, input, "AST_RULE_CASE(1)");
    print_state_test(check, "test_read_rule_case_simple (1)");
    struct ast_node *ast = ast_from_read(read_rule_case, input);
    check = ast->children[0]->type == AST_CASE_CLAUSE;
    print_state_test(check, "test_read_rule_case_simple (2)");
    ast_free(ast);
}

void test_read_rule_case_double(void)
{
    char *input = "case var\n\nin\ncase1)\nstart;;\ncase2)\nstop;;;\nesac";
    test_rule(read_rule_case, input, "AST_RULE_CASE(1)");
    struct ast_node *ast = ast_from_read(read_rule_case, input);
    bool check = ast->children[0]->type == AST_CASE_CLAUSE;
    print_state_test(check, "test_read_rule_case_double");
    ast_free(ast);
}

void test_read_rule_case_fail(void)
{
    char *input = "do\n\ndone";
    bool check = test_not_rule(read_rule_case, input);
    print_state_test(check, "test_read_rule_case_fail");
}

void test_read_rule_case(void)
{
    test_read_rule_case_simple();
    test_read_rule_case_double();
    test_read_rule_case_fail();
}