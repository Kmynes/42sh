#include "unit/parser/rules/test_rules.h"

void test_read_pipeline_simple(void)
{
    assert(test_rule(read_pipeline, "toto", "AST_PIPELINE(1)"));
    struct ast_node *ast = ast_from_read(read_pipeline, "toto");
    assert(ast->children[0]->type == AST_COMMAND);
    ast_free(ast);
}

void test_read_pipeline_negative(void)
{
    char *input = "!toto";
    assert(test_rule(read_pipeline, input, "AST_PIPELINE(1)_negative"));
    struct ast_node *ast = ast_from_read(read_pipeline, input);
    assert(ast->children[0]->type == AST_COMMAND);
    ast_free(ast);
}

void test_read_pipeline_multiple(void)
{
    char *input = "toto|titi";
    assert(test_rule(read_pipeline, input, "AST_PIPELINE(2)"));
    struct ast_node *ast = ast_from_read(read_pipeline, input);
    assert(ast->children[0]->type == AST_COMMAND);
    assert(ast->children[1]->type == AST_COMMAND);
    ast_free(ast);

    input = "toto|\n\ntiti";
    assert(test_rule(read_pipeline, input, "AST_PIPELINE(2)"));
    ast = ast_from_read(read_pipeline, input);
    assert(ast->children[0]->type == AST_COMMAND);
    assert(ast->children[1]->type == AST_COMMAND);
    ast_free(ast);

    input = "toto|\n\ntiti|tutu";
    assert(test_rule(read_pipeline, input, "AST_PIPELINE(3)"));
    ast = ast_from_read(read_pipeline, input);
    assert(ast->children[0]->type == AST_COMMAND);
    assert(ast->children[1]->type == AST_COMMAND);
    assert(ast->children[2]->type == AST_COMMAND);
    ast_free(ast);
}

void test_read_pipeline_fail(void)
{
    test_not_rule(read_pipeline, " toto");
}

void test_read_pipeline(void)
{
    test_read_pipeline_simple();
    test_read_pipeline_negative();
    test_read_pipeline_multiple();
    test_read_pipeline_fail();
}