#include "unit/parser/rules/test_rules.h"

void test_read_pipeline_simple(void)
{
    test_rule(read_pipeline, "toto", "pipeline");
    struct ast_node *ast = ast_from_read(read_pipeline, "toto");
    assert(ast->nb_children == 1);
    assert(ast->children[0]->type == AST_COMMAND);
    ast_free(ast);
}

void test_read_pipeline_negative(void)
{
    char *input = "!toto";
    test_rule(read_pipeline, input, "pipeline_negative");
    struct ast_node *ast = ast_from_read(read_pipeline, input);
    assert(ast->nb_children == 1);
    assert(ast->children[0]->type == AST_COMMAND);
    ast_free(ast);
}

void test_read_pipeline_multiple(void)
{
    char *input = "toto|titi";
    test_rule(read_pipeline, input, "pipeline");
    struct ast_node *ast = ast_from_read(read_pipeline, input);
    assert(ast->nb_children == 2);
    assert(ast->children[0]->type == AST_COMMAND);
    assert(ast->children[1]->type == AST_COMMAND);
    ast_free(ast);

    input = "toto|\n\ntiti";
    test_rule(read_pipeline, input, "pipeline");
    ast = ast_from_read(read_pipeline, input);
    assert(ast->nb_children == 2);
    assert(ast->children[0]->type == AST_COMMAND);
    assert(ast->children[1]->type == AST_COMMAND);
    ast_free(ast);

    input = "toto|\n\ntiti|tutu";
    test_rule(read_pipeline, input, "pipeline");
    ast = ast_from_read(read_pipeline, input);
    assert(ast->nb_children == 3);
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