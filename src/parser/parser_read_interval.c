#include "parser.h"

bool parser_readeol(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (OPTIONAL(parser_readchar(p, '\r')) && parser_readchar(p, '\n'))
        return true;

    p->cursor = tmp;
    return false;
}

bool parser_readidentifier(struct parser *p)
{
    if (parser_readletter(p) && ZERO_OR_MANY(parser_readalphanum(p)))
        return true;
    return false;
}

bool parser_readinteger(struct parser *p)
{
    if (ONE_OR_MANY(parser_readnum(p)))
        return true;
    return false;
}