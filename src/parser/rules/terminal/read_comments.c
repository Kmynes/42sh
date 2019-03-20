#include <parser/rules/rules.h>

bool read_comment(struct parser *p)
{
    int tmp = p->cursor;

    if (read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_spaces(p)
        && parser_readchar(p, '#')
        && ZERO_OR_MANY(parser_readoutset(p, "\n"))
        && (parser_readchar(p, '\n') || read_eof(p))
        )
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}