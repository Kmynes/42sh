#include "parser.h"

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
    if (p->input[p->cursor] == c)
    {
        p->cursor++;
        return true;
    }
    else
        return false;
}