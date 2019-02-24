#include "rules.h"

bool read_spaces(struct parser *p)
{
    int tmp = p->cursor;
    if (ZERO_OR_MANY(parser_readinset(p, " \t")))
        return true;

    p->cursor = tmp;
    return false;
}