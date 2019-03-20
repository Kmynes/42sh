#include "unit/parser/rules/test_rules.h"

void test_read_case_item_simplest(void)
{
    char *input = "(toto)";
    bool check = test_rule(read_case_item, input, "AST_CASE_ITEM(0)");
    print_state_test(check, "test_read_case_item_simplest");

    struct ast_node *ast = ast_from_read(read_case_item, input);
    ast_free(ast);
}

void test_read_case_item_simple(void)
{
    char *input = "(toto)\ntutu&&titi;tata||toto;\n";
    bool check = test_rule(read_case_item, input, "AST_CASE_ITEM(1)");
    print_state_test(check, "test_read_case_item_simple (1)");

    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;
    check = words->nb_word == 1;
    print_state_test(check, "test_read_case_item_simple (2)");

    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_case_item_simple (3)");
    ast_free(ast);
}

void test_read_case_item_simple2(void)
{
    char *input = "toto)\ntutu&&titi;\ntata||toto;\n";
    bool check = test_rule(read_case_item, input, "AST_CASE_ITEM(1)");
    print_state_test(check, "test_read_case_item_simple2 (1)");

    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;

    check = words->nb_word == 1;
    print_state_test(check, "test_read_case_item_simple2 (2)");

    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_case_item_simple2 (3)");
    ast_free(ast);
}

void test_read_case_item_multiple(void)
{
    char *input = "toto|titi|titi|tata)\ntutu&&titi;\ntata||toto;\n";
    bool check = test_rule(read_case_item, input, "AST_CASE_ITEM(1)");
    print_state_test(check, "test_read_case_item_multiple (1)");

    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;

    check = words->nb_word == 4;
    print_state_test(check, "test_read_case_item_multiple (2)");

    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_case_item_multiple (3)");

    ast_free(ast);
}


void test_read_case_item_fail(void)
{
    char *input = "(toto";
    bool check = test_not_rule(read_case_item, input);
    print_state_test(check, "test_read_case_item_fail");
}

void test_read_case_item(void)
{
    test_read_case_item_simplest();
    test_read_case_item_simple();
    test_read_case_item_simple2();
    test_read_case_item_multiple();
    test_read_case_item_fail();
}