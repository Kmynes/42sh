#include "unit/parser/rules/test_rules.h"

void test_read_pipeline_simple(void)
{
    bool check = test_rule(read_pipeline, "toto", "AST_PIPELINE(1)");
    print_state_test(check, "test_read_pipeline_simple (1)");

    struct ast_node *ast = ast_from_read(read_pipeline, "toto");
    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_simple (2)");

    ast_free(ast);
}

void test_read_pipeline_negative(void)
{
    char *input = "!toto";
    bool check = test_rule(read_pipeline, input, "AST_PIPELINE(1)_negative");
    print_state_test(check, "test_read_pipeline_negative (1)");

    struct ast_node *ast = ast_from_read(read_pipeline, input);
    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_negative (2)");

    ast_free(ast);
}

void test_read_pipeline_multiple(void)
{
    char *input = "toto|titi";
    bool check = test_rule(read_pipeline, input, "AST_PIPELINE(2)");
    print_state_test(check, "test_read_pipeline_multiple (1)");

    struct ast_node *ast = ast_from_read(read_pipeline, input);
    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (2)");

    check = ast->children[1]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (3)");
    ast_free(ast);

    input = "toto|\n\ntiti";
    check = test_rule(read_pipeline, input, "AST_PIPELINE(2)");
    print_state_test(check, "test_read_pipeline_multiple (4)");
    ast = ast_from_read(read_pipeline, input);

    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (5)");

    check = ast->children[1]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (6)");
    ast_free(ast);

    input = "toto|\n\ntiti|tutu";
    check = test_rule(read_pipeline, input, "AST_PIPELINE(3)");
    print_state_test(check, "test_read_pipeline_multiple (7)");
    ast = ast_from_read(read_pipeline, input);

    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (8)");

    check = ast->children[1]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (9)");

    check = ast->children[2]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_multiple (10)");
    ast_free(ast);
}

void test_read_pipeline_tricky(void)
{
    char *input = "toto||tutu";
    bool check = test_rule(read_pipeline, input, "AST_PIPELINE(1)");
    print_state_test(check, "test_read_pipeline_tricky (1)");

    struct ast_node *ast = ast_from_read(read_pipeline, input);
    check = ast->children[0]->type == AST_COMMAND;
    print_state_test(check, "test_read_pipeline_tricky (2)");

    ast_free(ast);
}

void test_read_pipeline_fail(void)
{
    bool check = test_not_rule(read_pipeline, " toto");
    print_state_test(check, "test_read_pipeline_fail");
}

void test_read_pipeline(void)
{
    test_read_pipeline_simple();
    test_read_pipeline_negative();
    test_read_pipeline_multiple();
    test_read_pipeline_fail();
    test_read_pipeline_tricky();
}