#include "parser/rules/rules.h"

bool read_value(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ONE_OR_MANY(parser_readoutset(p, " \t\r\n")))
        return true;

    p->cursor = tmp;
    return false;
}