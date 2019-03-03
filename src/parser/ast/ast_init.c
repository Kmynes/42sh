#include "ast.h"

struct ast_node_free free_table[] = {
        { AST_NODE_ASSIGN, ast_assign_free },
        { AST_NODE_SECTION, ast_section_free },
        { AST_NODE_KEY_VALUE, ast_key_value_free },
        { 0, NULL }  // always last element
};

struct ast_node *ast_init(enum ast_node_type type, void *data)
{
    struct ast_node *ast = malloc(sizeof(struct ast_node));

    ast->type = type;
    ast->data = data;
    // 10 children max
    ast->children = malloc(sizeof(struct ast_node) * 10);
    ast->nb_children = 0;
    ast->capacity = 10;

    return ast;
}

void ast_free(struct ast_node *ast)
{
    if (ast == NULL)
        return;

    for (int i = 0; free_table[i].type; i++)
    {
        if (free_table[i].type == ast->type)
            free_table[i].free_function(ast->data);
    }

    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->children[i]);

    free(ast->children); // free array
    free(ast->data);
    free(ast);
}