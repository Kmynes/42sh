#include <parser/rules/rules.h>

bool read_assignment_word(struct parser *p)
{
    int tmp = p->cursor;

    if (read_identifier(p) && parser_readchar(p, '=') && read_word(p))
    {
        return true;
    }

    p->cursor = tmp;
    return false;
}