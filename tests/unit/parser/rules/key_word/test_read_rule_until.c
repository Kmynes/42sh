#include "unit/parser/rules/test_rules.h"

void test_read_rule_until_simple(void)
{
    char *input = "until\n\necho hello\ndo\nls\ndone";
    assert(test_rule(read_rule_until, input, "AST_RULE_UNTIL(2)"));
    struct ast_node *ast = ast_from_read(read_rule_until, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    assert(ast->children[1]->type == AST_DO_GROUP);
    ast_free(ast);
}

void test_read_rule_until_complex(void)
{
    char *input = "until\n\necho toto;\necho titi\necho"
                  "tutu\ndo\nls;cat;find;\ndone";
    assert(test_rule(read_rule_until, input, "AST_RULE_UNTIL(2)"));
    struct ast_node *ast = ast_from_read(read_rule_until, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    assert(ast->children[1]->type == AST_DO_GROUP);
    ast_free(ast);
}

void test_read_rule_until_fail(void)
{
    char *input = "echo toto";
    assert(test_not_rule(read_rule_until, input));
}

void test_read_rule_until(void)
{
    test_read_rule_until_simple();
    test_read_rule_until_complex();
    test_read_rule_until_fail();
}