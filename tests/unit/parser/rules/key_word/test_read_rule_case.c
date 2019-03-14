#include "unit/parser/rules/test_rules.h"

void test_read_rule_case_simple(void)
{
    char *input = "case var in\ncase1)\nstart\n;;esac";
    assert(test_rule(read_rule_case, input, "AST_RULE_CASE(1)"));
    struct ast_node *ast = ast_from_read(read_rule_case, input);
    assert(ast->children[0]->type == AST_CASE_CLAUSE);
    ast_free(ast);
}

void test_read_rule_case_double(void)
{
    char *input = "case var\n\nin\ncase1)\nstart;;\ncase2)\nstop;;;\nesac";
    test_rule(read_rule_case, input, "AST_RULE_CASE(1)");
    struct ast_node *ast = ast_from_read(read_rule_case, input);
    assert(ast->children[0]->type == AST_CASE_CLAUSE);
    ast_free(ast);
}

void test_read_rule_case_fail(void)
{
    char *input = "do\n\ndone";
    assert(test_not_rule(read_rule_case, input));
}

void test_read_rule_case(void)
{
    test_read_rule_case_simple();
    test_read_rule_case_double();
    test_read_rule_case_fail();
}