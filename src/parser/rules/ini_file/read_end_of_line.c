#include "parser/rules/rules.h"

bool read_end_of_line(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (OPTIONAL(parser_readchar(p, '\r')) && parser_readchar(p, '\n'))
        return true;

    p->cursor = tmp;
    return false;
}