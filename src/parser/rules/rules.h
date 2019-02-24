#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

//parser_character

bool parser_readalpha(struct parser *p);

bool parser_readnum(struct parser *p);

bool parser_readletter(struct parser *p);

bool parser_readalphanum(struct parser *p);

bool parser_readeol(struct parser *p);

bool parser_readidentifier(struct parser *p);

bool parser_readinteger(struct parser *p);

//parser_capture
char *extract_string(char *s, int begin, int end);

void print_capture(struct parser *p, struct list_capt_s *capture);

void free_list_capt_s(struct list_capt_s *capture);

struct list_capt_s *list_capt_init(void);

void list_capt_store(struct list_capt_s *, const char *, struct capture_s *);

struct capture_s *list_capt_lookup(struct list_capt_s *, const char *);

static inline bool parser_begin_capture(struct parser *p, const char *tag)
{
    struct capture_s capt = { p->cursor, 0 };
    list_capt_store(p->capture, tag, &capt);
    return true;
}

static inline char *parser_get_capture(struct parser *p, const char *tag)
{
    struct capture_s *pcapt = list_capt_lookup(p->capture, tag);
    if (!pcapt)
        return false;
    return strndup(&p->input[pcapt->begin], pcapt->end - pcapt->begin);
}

static inline bool parser_end_capture(struct parser *p, const char *tag)
{
    struct capture_s *pcapt = list_capt_lookup(p->capture, tag);
    if (!pcapt)
        return false;
    pcapt->end = p->cursor;
    return true;
}

//ast
struct ast_node *ast_init(void);

void ast_free(struct ast_node *ast);

void ast_assign_free(struct ast_assign *ast_assign);

void ast_key_value_free(struct ast_key_value *ast_key_value);

void ast_section_free(struct ast_section *ast_sec);

void ast_store(struct parser *p, enum ast_node_type type, struct ast_assign
*ast_assign);
// coder ast_lookup : renvoie un ast_node en cherchant le premier tag qui match
struct ast_node *ast_lookup(struct parser *p, const char *tag);

void ast_set_in_parent(struct ast_node *parent, struct ast_node *ast);
struct ast_node *ast_get_from_parent(struct ast_node *parent, enum ast_node_type type_ast_search);

void ast_set_in_parser(struct parser *p, struct ast_node *ast);
struct ast_node *ast_get_from_parser(struct parser *p, enum ast_node_type type_ast_search);

bool parser_readassign(struct parser *p);