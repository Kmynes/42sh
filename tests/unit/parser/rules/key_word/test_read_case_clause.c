#include "unit/parser/rules/test_rules.h"

void test_read_case_clause_simple(void)
{
    char *input = "(toto)\ntutu&&titi;tata||toto;\n";
    assert(test_rule(read_case_clause, input, "AST_CASE_CLAUSE(1)"));
    struct ast_node *ast = ast_from_read(read_case_clause, input);
    assert(ast->children[0]->type == AST_CASE_ITEM);
    ast_free(ast);
}

void test_read_case_clause_double(void)
{
    char *input = "(case1)\ntutu&&titi;\ntata||toto;\n;;\n(case2)";
    test_rule(read_case_clause, input, "AST_CASE_CLAUSE(2)");
    struct ast_node *ast = ast_from_read(read_case_clause, input);
    assert(ast->children[0]->type == AST_CASE_ITEM);
    assert(ast->children[1]->type == AST_CASE_ITEM);
    ast_free(ast);
}

void test_read_case_clause_multiple(void)
{
    char *input = "case1)\nfind;\n;;\n(case2)\nls;;;(case3)cat;";
    assert(test_rule(read_case_clause, input, "AST_CASE_CLAUSE(3)"));
    struct ast_node *ast = ast_from_read(read_case_clause, input);
    assert(ast->children[0]->type == AST_CASE_ITEM);
    assert(ast->children[1]->type == AST_CASE_ITEM);
    assert(ast->children[2]->type == AST_CASE_ITEM);
    ast_free(ast);
}


void test_read_case_clause_fail(void)
{
    char *input = "(toto";
    assert(test_not_rule(read_case_clause, input));
}


void test_read_case_clause(void)
{
    test_read_case_clause_simple();
    test_read_case_clause_double();
    test_read_case_clause_multiple();
    test_read_case_clause_fail();
}