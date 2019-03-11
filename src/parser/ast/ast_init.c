#include "ast.h"
#include <stdlib.h>

struct ast_node *ast_init(enum ast_node_type type, void *data)
{
    struct ast_node *ast = malloc(sizeof(struct ast_node));

    ast->type = type;
    ast->data = data;
    // 10 children max
    ast->children = malloc(sizeof(struct ast_node) * 10);
    ast->nb_children = 0;
    ast->capacity = 10;
    ast->free = NULL;
    ast->exec = NULL;
    ast->exec_arg = NULL;
    ast->to_string = ast_node_default_to_string;
    ast->custom_to_string = false;

    return ast;
}

char *ast_node_default_to_string(struct ast_node *ast)
{
    char *output = malloc(30);
    sprintf(output, "%s(%ld)", (char *)AST_STRING[ast->type],
        ast->nb_children);
    return output;
}

void ast_free(struct ast_node *ast)
{
    if (ast == NULL)
        return;

    if (ast->free != NULL)
        ast->free(ast->data);

    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->children[i]);

    free(ast->children); // free array
    free(ast);
}