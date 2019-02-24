#include "rules.h"

struct ast_node *ast_init(void)
{
    struct ast_node *ast = malloc(sizeof(struct ast_node));

    ast->type = AST_NODE_EMPTY;
    ast->data = NULL;
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

    if (ast->type == AST_NODE_SECTION)
        ast_section_free(ast->data);
    else if (ast->type == AST_NODE_KEY_VALUE)
        ast_key_value_free(ast->data);
    else if (ast->type == AST_NODE_ASSIGN)
        ast_assign_free(ast->data);

    for (size_t i = 0; i < ast->nb_children; i++)
        ast_free(ast->children[i]);

    free(ast->children); // free array
    free(ast);
}

void ast_assign_free(struct ast_assign *ast_assign)
{
    free(ast_assign->id);
    free(ast_assign->num);
    free(ast_assign);
}

void ast_key_value_free(struct ast_key_value *ast_key_value)
{
    free(ast_key_value->id);
    free(ast_key_value->value);
    free(ast_key_value);
}

void ast_section_free(struct ast_section *ast_sec)
{
    free(ast_sec->identifier);
    free(ast_sec);
}
/**
 * store new ast_node at top of ast
 * @param p
 * @param tag
 * @param ast
 */
void ast_store(struct parser *p, enum ast_node_type type, struct ast_assign
*ast_assign)
{
    struct ast_node *ast = ast_init();
    ast->type = type;

    if (ast->type == AST_NODE_ASSIGN)
    {
        // copy of struct ast_asssign on heap
        void *node_data = malloc(sizeof(struct ast_assign));
        memcpy(node_data, ast_assign, sizeof(struct ast_assign));
        ast->data = node_data;
    }
    ast->children[ast->nb_children] = p->ast;
    ast->nb_children++;
    p->ast = ast;
}

void ast_set_in_parent(struct ast_node *parent, struct ast_node *ast)
{
    if (parent->nb_children == parent->capacity)
    {
        struct ast_node **tmp = realloc(parent->children, sizeof(struct ast_node) * parent->capacity * 2);
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

struct ast_node *ast_get_from_parent(struct ast_node *parent, enum ast_node_type type_ast_search)
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
    ast_set_in_parent(p->ast, ast);
}

struct ast_node *ast_get_from_parser(struct parser *p, enum ast_node_type type_ast_search)
{
    return ast_get_from_parent(p->ast, type_ast_search);
}