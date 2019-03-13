#include "unit/parser/rules/test_rules.h"

void test_read_rule_for1(void)
{
    char *input = "for var do\n\ntcheck=true;\ndone";
    test_rule(read_rule_for, input, "AST_RULE_FOR(1)");
}

void test_read_rule_for2(void)
{
    char *input = "for var ;\n\n\ndo\n\ntcheck=true;\ndone";
    test_rule(read_rule_for, input, "AST_RULE_FOR(1)");
}

void test_read_rule_for3(void)
{
    char *input = "for var \n\n\n in toto tata titi \n do\n\ntcheck=true;\ndone";
    test_rule(read_rule_for, input, "AST_RULE_FOR(1)");
}

void test_read_rule_for(void)
{
    test_read_rule_for1();
    test_read_rule_for2();
    test_read_rule_for3();
}