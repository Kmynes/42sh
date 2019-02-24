#pragma once

#include "rules/rules.h"

#define OPTIONAL(R) \
__extension__({     \
    R;              \
    1;              \
})

#define ZERO_OR_MANY(R)\
__extension__({        \
    while(R);          \
    1;                 \
})

#define ONE_OR_MANY(R)    \
__extension__({     \
    int res = 0;\
    if (R)          \
    {               \
        while (R);  \
        res = 1; \
    }               \
    res;	        \
})

struct parser
{
    char *input;
    int cursor;
    struct list_capt_s *capture;
    struct ast_node *ast;
    struct error_s *error;
};

enum error_type_e
{
    ON_CHAR,
    ON_TEXT,
    ON_RANGE,
    ON_INSET,
    ON_OUTSET
};

struct error_s
{
    enum error_type_e type;
    union
    {
        char c;
        char *text;
        char *inset;
        char *outset;
        struct
        {
            char begin;
            char end;
        } range;
    } u;
};

enum ast_node_type
{
    AST_NODE_EMPTY,
    AST_NODE_INI_FILE,
    AST_NODE_SECTION,
    AST_NODE_KEY_VALUE,
    AST_NODE_ASSIGN
};

struct ast_node
{
    enum ast_node_type type;
    void *data;
    size_t nb_children;
    size_t capacity;
    struct ast_node **children; // array of children
};

struct ast_section
{
    char *identifier;
};

struct ast_key_value
{
    char *id;
    char *value;
};

struct ast_assign
{
    char *id;
    char *num;
};

struct parser *parser_new_from_string(const char *text);

void parser_free(struct parser *p);

bool parser_eof(struct parser *p);

char parser_getchar(struct parser *p);

bool parser_peekchar(struct parser * p, char c);

bool parser_readchar(struct parser *p, char c);

bool parser_readtext(struct parser *p, char *text);

bool parser_readrange(struct parser *p, char begin, char end);

bool parser_readinset(struct parser *p, char *set);

bool parser_readoutset(struct parser *p, char *set);