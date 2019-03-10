#include <parser/parser.h>

void ast_set_in_parent(struct ast_node *parent, struct ast_node *ast)
{
    if (parent->nb_children == parent->capacity)
    {
        struct ast_node **tmp = realloc(parent->children,
            sizeof(struct ast_node) * parent->capacity * 2);
        if (!tmp)
        {
            //catch error memory
            return;
        }
        parent->children = tmp;
        parent->capacity *= 2;
        parent->children[parent->nb_children++] = ast;
    }
    else
        parent->children[parent->nb_children++] = ast;
}

struct ast_node *ast_get_from_parent(struct ast_node *parent,
    enum ast_node_type type_ast_search)
{
    struct ast_node *child = NULL;
    for (size_t i = 0; i < parent->nb_children; i++)
    {
        child = parent->children[i];
        if (child->type == type_ast_search)
        {
            parent->children[i] = NULL;
            size_t n = (parent->nb_children - i) * sizeof(struct ast_node*);
            void *src = parent->children + (i + 1);
            void *dest = parent->children + i;
            memmove(dest, src, n);
            parent->nb_children--;
            return child;
        }
    }
    return NULL;
}

void ast_set_in_parser(struct parser *p, struct ast_node *ast)
{
    if (ast != NULL)
        ast_set_in_parent(p->ast, ast);
}

struct ast_node *ast_get_from_parser(struct parser *p,
    enum ast_node_type type_ast_search)
{
    return ast_get_from_parent(p->ast, type_ast_search);
}

void ast_recover_all_from_parser(struct ast_node *parent, struct parser *p,
    enum ast_node_type type)
{
    struct ast_node *child = NULL;
    while ((child = ast_get_from_parser(p, type)))
        ast_set_in_parent(parent, child);
}