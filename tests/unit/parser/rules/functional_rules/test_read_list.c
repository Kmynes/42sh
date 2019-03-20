#include "unit/parser/rules/test_rules.h"

void test_read_list_simple(void)
{
    char *input = "toto;";
    bool check = test_rule(read_list, input, "AST_LIST(1)");
    print_state_test(check, "test_read_list_simple (1)");

    struct ast_node *ast = ast_from_read(read_list, input);
    check = ast->children[0]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_simple (2)");

    ast_free(ast);
}

void test_read_list_double(void)
{
    char *input = "toto;titi;";
    bool check = test_rule(read_list, input, "AST_LIST(3)");
    print_state_test(check, "test_read_list_double (1)");

    struct ast_node *ast = ast_from_read(read_list, input);
    check = ast->children[0]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_double (2)");

    check = ast->children[1]->type == AST_WORD;
    print_state_test(check, "test_read_list_double (3)");

    check = strcmp(ast->children[1]->data, ";") == 0;
    print_state_test(check, "test_read_list_double (4)");

    check = ast->children[2]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_double (5)");

    ast_free(ast);
}

void test_read_list_triple(void)
{
    char *input = "toto;titi&tutu&";
    test_rule(read_list, input, "AST_LIST(5)");
    struct ast_node *ast = ast_from_read(read_list, input);
    bool check = ast->children[0]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_triple (1)");

    check = ast->children[1]->type == AST_WORD;
    print_state_test(check, "test_read_list_triple (2)");

    check = strcmp(ast->children[1]->data, ";") == 0;
    print_state_test(check, "test_read_list_triple (3)");

    check = ast->children[2]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_triple (4)");

    check = ast->children[3]->type == AST_WORD;
    print_state_test(check, "test_read_list_triple (5)");

    check = strcmp(ast->children[3]->data, "&") == 0;
    print_state_test(check, "test_read_list_triple (6)");

    check = ast->children[4]->type == AST_AND_OR;
    print_state_test(check, "test_read_list_triple (7)");

    ast_free(ast);
}

void test_read_list(void)
{
    test_read_list_simple();
    test_read_list_double();
    test_read_list_triple();
}