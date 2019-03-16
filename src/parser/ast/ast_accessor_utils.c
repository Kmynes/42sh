#include "ast.h"

void ast_recover_all_from_parser(struct ast_node *parent, struct parser *p,
    enum ast_node_type type)
{
    struct ast_node *child = NULL;
    while ((child = ast_get_from_parser(p, type)))
        ast_set_in_parent(parent, child);
}

void ast_delete_all_from_parser(struct parser *p, enum ast_node_type type)
{
    struct ast_node *ast_tmp = ast_init(AST_NODE_EMPTY, NULL);
    ast_recover_all_from_parser(ast_tmp, p, type);
    ast_free(ast_tmp);
}