#include "unit/parser/rules/test_rules.h"

void test_read_and_or_simple(void)
{
    char *input = "toto";

    bool check = test_rule(read_and_or, input, "AST_AND_OR(1)");
    print_state_test(check, "test_read_and_or_simple (1)");

    struct ast_node *ast = ast_from_read(read_and_or, input);
    check = ast->nb_children == 1;
    print_state_test(check, "test_read_and_or_simple (2)");

    check = ast->children[0]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_simple (3)");

    ast_free(ast);
}

void test_read_and_or_and(void)
{
    char *input = "toto&&\n\ntiti";
    bool check = test_rule(read_and_or, input, "AST_AND_OR(3)");
    print_state_test(check, "test_read_and_or_and (1)");

    struct ast_node *ast = ast_from_read(read_and_or, input);

    check = ast->children[0]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_and (2)");

    check = ast->children[1]->type == AST_WORD;
    print_state_test(check, "test_read_and_or_and (3)");

    check = ast->children[2]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_and (4)");

    ast_free(ast);
}

void test_read_and_or_or(void)
{
    char *input = "toto||titi";
    bool check = test_rule(read_and_or, input, "AST_AND_OR(3)");
    print_state_test(check, "test_read_and_or_or (1)");

    struct ast_node *ast = ast_from_read(read_and_or, input);
    check = ast->children[0]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_or (2)");

    check = ast->children[1]->type == AST_WORD;
    print_state_test(check, "test_read_and_or_or (3)");

    check = ast->children[2]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_or (4)");

    ast_free(ast);
}


void test_read_and_or_multiple(void)
{
    char *input = "toto||titi&&tutu||tata";
    bool check = test_rule(read_and_or, input, "AST_AND_OR(7)");
    print_state_test(check, "test_read_and_or_multiple (1)");

    struct ast_node *ast = ast_from_read(read_and_or, input);
    check = ast->children[0]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_multiple (2)");

    check = ast->children[1]->type == AST_WORD;
    print_state_test(check, "test_read_and_or_multiple (3)");

    check = ast->children[2]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_multiple (4)");

    check = ast->children[3]->type == AST_WORD;
    print_state_test(check, "test_read_and_or_multiple (5)");

    check = ast->children[4]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_multiple (6)");

    check = ast->children[5]->type == AST_WORD;
    print_state_test(check, "test_read_and_or_multiple (7)");

    check = ast->children[6]->type == AST_PIPELINE;
    print_state_test(check, "test_read_and_or_multiple (8)");

    ast_free(ast);
}

void test_read_and_or_fail(void)
{
    bool check = test_not_rule(read_and_or, " toto");
    print_state_test(check, "test_read_and_or_fail (1)");

    test_not_rule(read_and_or, "1deoi");
    print_state_test(check, "test_read_and_or_fail (2)");
}

void test_read_and_or(void)
{
    test_read_and_or_simple();
    test_read_and_or_and();
    test_read_and_or_or();
    test_read_and_or_multiple();
    test_read_and_or_fail();
}