#include "unit/parser/rules/test_rules.h"

void test_read_input_eof(void)
{
    char *input = "";
    bool check = test_rule(read_input, input, "AST_INPUT(0)");
    print_state_test(check, "test_read_input_eof");
}

void test_read_input_new_line(void)
{
    char *input = "\n";
    bool check = test_rule(read_input, input, "AST_INPUT(0)");
    print_state_test(check, "test_read_input_new_line");

    struct ast_node *ast = ast_from_read(read_input, input);
    ast_free(ast);
}

void test_read_input_simple(void)
{
    char *input = "toto\n";
    bool check = test_rule(read_input, input, "AST_INPUT(1)");
    print_state_test(check, "test_read_input_simple (1)");
    struct ast_node *ast = ast_from_read(read_input, input);

    check = ast->children[0]->type == AST_LIST;
    print_state_test(check, "test_read_input_simple (2)");

    ast_free(ast);
}

void test_read_input_simple2(void)
{
    char *input = "toto;";

    bool check = test_rule(read_input, input, "AST_INPUT(1)");
    struct ast_node *ast = ast_from_read(read_input, input);

    check = ast->children[0]->type == AST_LIST;
    print_state_test(check, "test_read_input_simple2 (2)");
    ast_free(ast);
}

void test_read_input_fail(void)
{
    char *input = ";\n";
    bool check = test_not_rule(read_input, input);
    print_state_test(check, "test_read_input_fail");
}

void test_read_input(void)
{
    test_read_input_new_line();
    test_read_input_eof();
    test_read_input_simple();
    test_read_input_simple2();
    test_read_input_fail();
}