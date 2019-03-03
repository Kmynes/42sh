#include "ast_print.h"
#include <parser/rules/rules.h>

struct ast_node_printer print_table[] = {
        { AST_NODE_ASSIGN, ast_assign_to_string },
        { 0, NULL }  // always last element
};

char *ast_node_to_string(struct ast_node *ast)
{
    for (int i = 0; print_table[i].type; i++)
    {
        if (print_table[i].type == ast->type)
            return print_table[i].print_function(ast);
    }

    return NULL;
}

