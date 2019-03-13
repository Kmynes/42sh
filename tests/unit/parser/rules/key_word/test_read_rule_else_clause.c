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

void test_read_rule_else_clause3(void)
{
    char *input = "elif\n\n!shool=Epita;\n\n\nthen\n\n!i=0;\n\n\n";
    char *input2 = "else\n\n!shool=Epita;\n\n\n";
    char buff[strlen(input) + strlen(input2)];
    sprintf(buff, "%s%s", input, input2);

    test_rule(read_rule_else_clause, buff, "AST_ELSE_CLAUSE(3)");
}

void test_read_rule_else_clause4(void)
{
    char *input = "elif\n\n!shool=Epita;\n\n\nthen\n\n!i=0;\n\n\n";
    char *input2 = "elif\n\n!shool=Epitech;\n\n\nthen\n\ndocker=compose;\n";
    char *input3 = "else\n\n!shool=42;\n\n\n";
    char buff[strlen(input) + strlen(input2) + strlen(input3)];
    sprintf(buff, "%s%s%s", input, input2, input3);

    test_rule(read_rule_else_clause, buff, "AST_ELSE_CLAUSE(3)");
}

void test_read_rule_else_clause(void)
{
    test_read_rule_else_clause1();
    test_read_rule_else_clause2();
    test_read_rule_else_clause3();
    test_read_rule_else_clause4();
}