#pragma once

#include <parser/parser.h>
#include <parser/rules/rules.h>

// ast_accessor
void ast_set_in_parent(struct ast_node *parent, struct ast_node *ast);
struct ast_node *ast_get_from_parent(struct ast_node *parent, enum ast_node_type type_ast_search);
void ast_set_in_parser(struct parser *p, struct ast_node *ast);
struct ast_node *ast_get_from_parser(struct parser *p, enum ast_node_type type_ast_search);

// ast_init
struct ast_node *ast_init(enum ast_node_type type, void *data);
void ast_free(struct ast_node *ast);
struct ast_node_free {
    enum ast_node_type type;
    void (*free_function)(void *);
};