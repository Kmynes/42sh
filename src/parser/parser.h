#pragma once

#include <stddef.h>
#include <lexer/lexer.h>

enum ast_node_type
{
    TYPE_INPUT,
    TYPE_LIST,
    TYPE_AND_OR,
    TYPE_PIPELINE,
    TYPE_COMMAND,
    TYPE_SIMPLE_COMMAND,
    TYPE_SHELL_COMMAND,
    TYPE_FUNCDEC,
    TYPE_REDIRECTION,
    TYPE_PREFIX,
    TYPE_ELEMENT,
    TYPE_COMPOUND_LIST,
    TYPE_RULE_FOR,
    TYPE_RULE_WHILE,
    TYPE_RULE_UNTIL,
    TYPE_RULE_CASE,
    TYPE_RULE_IF,
    TYPE_ELSE_CAUSE,
    TYPE_DO_GROUP,
    TYPE_CASE_CLAUSE,
    TYPE_CASE_ITEM
};

struct ast_node
{
    enum ast_node_type type;
    size_t nb_children;
    struct ast_node *children;
};

struct ast_node *parse(struct lexer *lexer);
