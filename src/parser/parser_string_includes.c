#include "parser.h"

bool parser_readtext(struct parser *p, char *text)
{
    int tmp = p->cursor;
    p->error->type = ON_CHAR;
    p->error->u.text = text;
    char *str = p->input + p->cursor;

    size_t len = strlen(text);
    if (strncmp(str, text, len) == 0)
    {
        p->cursor += len;
        return true;
    }

    p->cursor = tmp;
    return false;
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