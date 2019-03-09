#include "unit/parser/rules/test_rules.h"

void test_read_and_or_simple(void)
{
    char *input = "toto";
    assert(test_rule(read_and_or, input, "AST_AND_OR(1)"));
    struct ast_node *ast = ast_from_read(read_and_or, input);
    assert(ast->nb_children == 1);
    assert(ast->children[0]->type == AST_PIPELINE);
    ast_free(ast);
}

void test_read_and_or_and(void)
{
    char *input = "toto&&\n\ntiti";
    assert(test_rule(read_and_or, input, "AST_AND_OR(2)"));
    struct ast_node *ast = ast_from_read(read_and_or, input);
    assert(ast->nb_children == 2);
    assert(ast->children[0]->type == AST_PIPELINE);
    assert(ast->children[1]->type == AST_PIPELINE);
    ast_free(ast);
}

void test_read_and_or_or(void)
{
    char *input = "toto||titi";
    assert(test_rule(read_and_or, input, "AST_AND_OR(2)"));
    struct ast_node *ast = ast_from_read(read_and_or, input);
    printf("children : %ld\n", ast->nb_children);
//    printf("dfts: %s\n", ast_print_default(ast, "and_or"));
//    assert(ast->nb_children == 2);
//    assert(ast->children[0]->type == AST_PIPELINE);
//    assert(ast->children[1]->type == AST_PIPELINE);
    ast_free(ast);
}

void test_read_and_or_fail(void)
{
    test_not_rule(read_and_or, " toto");
    test_not_rule(read_and_or, "1deoi");
}

void test_read_and_or(void)
{
    test_read_and_or_simple();
    test_read_and_or_and();
//    test_read_and_or_or();
    test_read_and_or_fail();
}