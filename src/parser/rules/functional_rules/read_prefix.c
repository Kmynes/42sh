#include <parser/rules/rules.h>

bool read_prefix(struct parser *p)
{
    int tmp = p->cursor;

    if (read_assignment_word(p) == true || read_redirection(p) == true)
        return true;

    p->cursor = tmp;

    return false;
}
