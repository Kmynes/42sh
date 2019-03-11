#include "unit/parser/rules/test_rules.h"

void test_read_case_item_simple(void)
{
    char *input = "(toto)\ntutu&&titi;tata||toto;\n";
    assert(test_rule(read_case_item, input, "AST_CASE_ITEM(1)"));
    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;
    assert(words->nb_word == 1);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    ast_free(ast);
}

void test_read_case_item_simple2(void)
{
    char *input = "toto)\ntutu&&titi;\ntata||toto;\n";
    assert(test_rule(read_case_item, input, "AST_CASE_ITEM(1)"));
    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;
    assert(words->nb_word == 1);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    ast_free(ast);
}

void test_read_case_item_multiple(void)
{
    char *input = "toto|titi|titi|tata)\ntutu&&titi;\ntata||toto;\n";
    assert(test_rule(read_case_item, input, "AST_CASE_ITEM(1)"));
    struct ast_node *ast = ast_from_read(read_case_item, input);
    struct ast_multiple_word *words = ast->data;
    assert(words->nb_word == 4);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    ast_free(ast);
}


void test_read_case_item_fail(void)
{
    char *input = "toto)";
    assert(test_not_rule(read_case_item, input));
}


void test_read_case_item(void)
{
    test_read_case_item_simple();
    test_read_case_item_simple2();
    test_read_case_item_multiple();
    test_read_case_item_fail();
}