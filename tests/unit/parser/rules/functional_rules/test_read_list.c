#include "unit/parser/rules/test_rules.h"

void test_read_list_simple(void)
{
    char *input = "toto;";
    assert(test_rule(read_list, input, "AST_LIST(1)"));
    struct ast_node *ast = ast_from_read(read_list, input);
    assert(ast->children[0]->type == AST_AND_OR);
    ast_free(ast);
}

void test_read_list_double(void)
{
    char *input = "toto;titi;";
    assert(test_rule(read_list, input, "AST_LIST(3)"));
    struct ast_node *ast = ast_from_read(read_list, input);
    assert(ast->children[0]->type == AST_AND_OR);
    assert(ast->children[1]->type == AST_WORD);
    assert(strcmp((char *)ast->children[1]->data, ";") == 0);
    assert(ast->children[2]->type == AST_AND_OR);
    ast_free(ast);
}

void test_read_list_triple(void)
{
    char *input = "toto;titi&tutu&";
    test_rule(read_list, input, "AST_LIST(5)");
    struct ast_node *ast = ast_from_read(read_list, input);
    assert(ast->children[0]->type == AST_AND_OR);
    assert(ast->children[1]->type == AST_WORD);
    assert(strcmp((char *)ast->children[1]->data, ";") == 0);
    assert(ast->children[2]->type == AST_AND_OR);
    assert(ast->children[3]->type == AST_WORD);
    assert(strcmp((char *)ast->children[3]->data, "&") == 0);
    assert(ast->children[4]->type == AST_AND_OR);
    ast_free(ast);
}

void test_read_list(void)
{
    test_read_list_simple();
    test_read_list_double();
    test_read_list_triple();
}