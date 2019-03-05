#include "parser/rules/rules.h"

bool read_spaces(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (ZERO_OR_MANY(parser_readinset(p, " \t")))
        return true;

    p->cursor = tmp;
    return false;
}