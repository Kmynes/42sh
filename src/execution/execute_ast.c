#include "execute_ast.h"

int execute_ast(struct ast_node *ast)
{
    //make execution
    ast->children--;
    ast->children++;
    return 0;
}
