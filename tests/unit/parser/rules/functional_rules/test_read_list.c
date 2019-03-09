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
    test_rule(read_list, input, "AST_LIST(3)");
    struct ast_node *ast = ast_from_read(read_list, input);
//    printf("%s\n", ast_default_to_string(ast));
//    assert(ast->children[0]->type == AST_AND_OR);
//    assert(ast->children[1]->type == AST_WORD);
//    assert(ast->children[2]->type == AST_AND_OR);
    ast_free(ast);
}

void test_read_list(void)
{
    test_read_list_simple();
//    test_read_list_double();
}