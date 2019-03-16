#include <assert.h>
#include <stdbool.h>
#include <parser/parser.h>
#include <parser/rules/rules.h>

void test_ast_print(void)
{
    char *input = "echo toto";
    struct parser *p = parser_new_from_string(input);
    read_input(p);
    struct ast_node *ast = p->ast->children[0];
    ast_print(ast, NULL);
    parser_free(p);
}