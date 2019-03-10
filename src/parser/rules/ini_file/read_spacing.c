#include "parser/rules/rules.h"

bool read_spacing(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_spaces(p) && read_end_of_line(p))
        return true;

    p->cursor = tmp;

    if (parser_readchar(p, ';')
        && ZERO_OR_MANY(parser_readoutset(p, "\r\n"))
        && read_end_of_line(p))
        return true;

    p->cursor = tmp;
    return false;
}