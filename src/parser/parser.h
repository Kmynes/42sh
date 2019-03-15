#pragma once

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <errors.h>
#include "variables.h"

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

#define ONE_OR_MANY(R) \
__extension__({        \
    int res = 0;       \
    if (R)             \
    {                  \
        while (R);     \
        res = 1;       \
    }                  \
    res;	           \
})

struct parser
{
    char *input;
    unsigned int cursor;
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

#define FOREACH_AST(AST) \
        AST(AST_NODE_EMPTY)   \
        AST(AST_NODE_INI_FILE)  \
        AST(AST_NODE_SECTION)   \
        AST(AST_NODE_KEY_VALUE)  \
        AST(AST_NODE_ASSIGN)  \
        AST(AST_INPUT)  \
        AST(AST_LIST)  \
        AST(AST_AND_OR)  \
        AST(AST_PIPELINE)  \
        AST(AST_COMMAND)  \
        AST(AST_SIMPLE_COMMAND) \
        AST(AST_SHELL_COMMAND) \
        AST(AST_FUNCDEC) \
        AST(AST_REDIRECTION) \
        AST(AST_PREFIX) \
        AST(AST_ELEMENT) \
        AST(AST_COMPOUND_LIST) \
        AST(AST_RULE_FOR) \
        AST(AST_RULE_WHILE) \
        AST(AST_RULE_UNTIL) \
        AST(AST_RULE_CASE) \
        AST(AST_RULE_IF) \
        AST(AST_ELSE_CLAUSE) \
        AST(AST_DO_GROUP) \
        AST(AST_CASE_CLAUSE) \
        AST(AST_CASE_ITEM) \
        AST(AST_HEREDOC) \
        AST(AST_ASSIGNEMENT_WORD) \
        AST(AST_WORD) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum ast_node_type
{
    FOREACH_AST(GENERATE_ENUM)
};

//Global
extern const char *AST_STRING[];

// ast inifile
struct ast_node
{
    enum ast_node_type type;
    void *data;
    size_t nb_children;
    size_t capacity;
    struct ast_node **children; // array of children
    char *(*to_string)(struct ast_node *);
    int (*exec)(struct ast_node *);
    int (*exec_arg)(struct ast_node *, char *arg);
    bool custom_to_string;
    void (*free)(void *);
};

struct capture_s
{
    int begin;
    int end;
};

struct list_capt_s
{
    char *tag;
    struct capture_s capt;
    struct list_capt_s *next;
};

//parser_init
struct parser *parser_new_from_string(const char *text);
void parser_free(struct parser *p);
void parser_free_no_ast(struct parser *p);

//parser_character
bool parser_eof(struct parser *p);
char parser_getchar(struct parser *p);
bool parser_peekchar(struct parser *p, char c);
bool parser_readchar(struct parser *p, char c);
bool parser_readrange(struct parser *p, char begin, char end);

//parser_string_includes
bool parser_readtext(struct parser *p, char *text);
bool parser_readinset(struct parser *p, char *set);
bool parser_readoutset(struct parser *p, char *set);

//parser_read_alphanum
bool parser_readalpha(struct parser *p);
bool parser_readnum(struct parser *p);
bool parser_readletter(struct parser *p);
bool parser_readalphanum(struct parser *p);

//parser_read_interval
bool parser_readeol(struct parser *p);
bool parser_readidentifier(struct parser *p);
bool parser_readinteger(struct parser *p);

//parser_capture_init
void free_list_capt_s(struct list_capt_s *capture);
struct list_capt_s *list_capt_init(void);

//parser_capture
char *extract_string(char *s, int begin, int end);
void print_capture(struct parser *p, struct list_capt_s *capture);
struct list_capt_s *list_capt_store(struct list_capt_s *, const char *,
    struct capture_s *);
struct capture_s *list_capt_lookup(struct list_capt_s *, const char *);
void parser_remove_capture_by_tag(struct parser *p, const char *tag);
void parser_free_capture_list(struct parser *p);

static inline bool parser_begin_capture(struct parser *p, const char *tag)
{
    struct capture_s capt = { p->cursor, 0 };
    p->capture = list_capt_store(p->capture, tag, &capt);
    return true;
}

static inline char *parser_get_capture(struct parser *p, const char *tag)
{
    struct capture_s *pcapt = list_capt_lookup(p->capture, tag);
    if (!pcapt)
        return false;
    char *capture = strndup(&p->input[pcapt->begin],
        pcapt->end - pcapt->begin);
    parser_remove_capture_by_tag(p, tag);
    return capture;
}

static inline bool parser_end_capture(struct parser *p, const char *tag)
{
    struct capture_s *pcapt = list_capt_lookup(p->capture, tag);
    if (!pcapt)
        return false;
    pcapt->end = p->cursor;
    return true;
}

//ast_print
int ast_print(struct ast_node *ast, FILE *stream);
