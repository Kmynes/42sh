#include "rules.h"

bool read_identifier(struct parser *p)
{
    int tmp = p->cursor;

    if (parser_readletter(p) && ZERO_OR_MANY(parser_readalphanum(p)))
        return true;

    p->cursor = tmp;
    return false;
}