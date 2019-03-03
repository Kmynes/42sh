#pragma once

#include <parser/parser.h>

struct ast_node_printer {
    enum ast_node_type type;
    char *(*print_function)(struct ast_node *);
};

char *ast_node_to_string(struct ast_node *ast);