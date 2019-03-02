#include <parser/rules/rules.h>

bool read_compound_list(struct parser *p)
{
    int tmp = p->cursor;

    if (ZERO_OR_MANY(parser_readchar(p, '\n'))

    ) {
        return true;
    }

    p->cursor = tmp;

    return false;
}