#include "unit/parser/rules/test_rules.h"

void test_read_case_clause_simple(void)
{
    char *input = "(toto)\ntutu&&titi;tata||toto;\n";
    bool check = test_rule(read_case_clause, input, "AST_CASE_CLAUSE(1)");
    print_state_test(check, "test_read_case_clause_simple (1)");

    struct ast_node *ast = ast_from_read(read_case_clause, input);
    check = ast->children[0]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_simple (2)");
    ast_free(ast);
}

void test_read_case_clause_double(void)
{
    char *input = "(case1)\ntutu&&titi;\ntata||toto;\n;;\n(case2)";
    test_rule(read_case_clause, input, "AST_CASE_CLAUSE(2)");
    struct ast_node *ast = ast_from_read(read_case_clause, input);
    bool check = ast->children[0]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_double (1)");

    check = ast->children[1]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_double (2)");
    ast_free(ast);
}

void test_read_case_clause_multiple(void)
{
    char *input = "case1)\nfind;\n;;\n(case2)\nls;;;(case3)cat;";
    bool check = test_rule(read_case_clause, input, "AST_CASE_CLAUSE(3)");
    print_state_test(check, "test_read_case_clause_multiple (1)");
    struct ast_node *ast = ast_from_read(read_case_clause, input);
    check = ast->children[0]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_multiple (2)");

    check = ast->children[1]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_multiple (3)");

    check = ast->children[2]->type == AST_CASE_ITEM;
    print_state_test(check, "test_read_case_clause_multiple (4)");

    ast_free(ast);
}


void test_read_case_clause_fail(void)
{
    char *input = "(toto";
    bool check = test_not_rule(read_case_clause, input);
    print_state_test(check, "test_read_case_clause_fail");
}


void test_read_case_clause(void)
{
    test_read_case_clause_simple();
    test_read_case_clause_double();
    test_read_case_clause_multiple();
    test_read_case_clause_fail();
}