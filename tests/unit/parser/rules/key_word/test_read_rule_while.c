#include "unit/parser/rules/test_rules.h"

void test_read_rule_while_simple(void)
{
    char *input = "while\n\necho hello\ndo\nls\ndone";
    test_rule(read_rule_while, input, "AST_RULE_WHILE(2)");
    struct ast_node *ast = ast_from_read(read_rule_while, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    assert(ast->children[1]->type == AST_DO_GROUP);
    ast_free(ast);
}

void test_read_rule_while_complex(void)
{
    char *input = "while\n\necho toto;\necho titi\necho tutu\ndo\nls;cat;find;\ndone";
    test_rule(read_rule_while, input, "AST_RULE_WHILE(2)");
    struct ast_node *ast = ast_from_read(read_rule_while, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    assert(ast->children[1]->type == AST_DO_GROUP);
    ast_free(ast);
}

void test_read_rule_while_fail(void)
{
    char *input = "echo toto";
    assert(test_not_rule(read_rule_while, input));
}

void test_read_rule_while(void)
{
    test_read_rule_while_simple();
    test_read_rule_while_complex();
    test_read_rule_while_fail();
}