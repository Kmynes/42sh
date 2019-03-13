#include "unit/parser/rules/test_rules.h"

void test_read_rule_else_clause1(void)
{
    char *input = malloc(sizeof(char) * 512);
    strcpy(input, "else\n\n!i=0;\n\n\n");

    test_rule(read_rule_else_clause, input, "AST_ELSE_CLAUSE(1)");
    free(input);
}

void test_read_rule_else_clause2(void)
{
    char *input = malloc(sizeof(char) * 512);
    strcpy(input, "elif\n\n!shool=Epita;\n\n\nthen\n\n!i=0;\n\n\n");

    test_rule(read_rule_else_clause, input, "AST_ELSE_CLAUSE(2)");
    free(input);
}

void test_read_rule_else_clause(void)
{
    test_read_rule_else_clause1();
    test_read_rule_else_clause2();
}