#include "parser.h"

struct parser *parser_new_from_string(const char *text)
{
    struct parser *parser = malloc(sizeof(struct parser));
    size_t len = strlen(text);
    parser->input = malloc(len + 1);
    strcpy(parser->input, text);
    parser->cursor = 0;
    parser->capture = list_capt_init();
    parser->ast = ast_init();
    parser->error = malloc(sizeof(struct error_s));

    return parser;
}

void parser_free(struct parser *p)
{
    if (p)
    {
        free(p->input);
        free_list_capt_s(p->capture);
        ast_free(p->ast);
        free(p->error);
        free(p);
    }
}

bool parser_eof(struct parser *p)
{
    return p->input[p->cursor] == 0;
}

char parser_getchar(struct parser *p)
{
    return p->input[p->cursor++];
}

bool parser_peekchar(struct parser * p, char c)
{
    if (p->input[p->cursor] == c)
        return true;
    else
        return false;
}

bool parser_readchar(struct parser *p, char c)
{
    p->error->type = ON_CHAR;
    p->error->u.c = c;
    if( p->input[p->cursor] == c)
    {
        p->cursor++;
        return true;
    }
    else
        return false;
}

bool parser_readtext(struct parser *p, char *text)
{
    p->error->type = ON_CHAR;
    p->error->u.text = text;
    char *str = p->input + p->cursor;

    while (*text)
    {
        if (*str != *text)
            return false;
        str++;
        text++;
    }

    return true;
}

bool parser_readrange(struct parser *p, char begin, char end)
{
    p->error->type = ON_RANGE;
    p->error->u.range.begin = begin;
    p->error->u.range.end = end;
    char c = p->input[p->cursor];
    if (c >= begin && c <= end)
    {
        p->cursor++;
        return true;
    }

    return false;
}

bool parser_readinset(struct parser *p, char *set)
{
    p->error->type = ON_INSET;
    p->error->u.inset = set;
    char c = p->input[p->cursor];
    size_t len_set = strlen(set);
    for (size_t i = 0; i < len_set; i++)
    {
        if (c == set[i])
        {
            p->cursor++;
            return true;
        }
    }

    return false;
}

bool parser_readoutset(struct parser *p, char *set)
{
    p->error->type = ON_OUTSET;
    p->error->u.outset = set;
    char c = p->input[p->cursor];

    if (!c)
        return false;

    for (size_t i = 0; i < strlen(set); i++)
    {
        if (c == set[i])
        {
            return false;
        }
    }

    p->cursor++;
    return true;
}