#include <parser/rules/rules.h>

static bool read_optional_instructions(struct parser *p)
{
    int tmp = p->cursor;

    if (parser_readchar(p, '|')                 &&
        ZERO_OR_MANY(parser_readchar(p, '\n'))  &&
        read_command(p)  
    )
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_pipeline(struct parser *p)
{
    int tmp = p->cursor;

    if (OPTIONAL(parser_readchar(p, '!')) &&
        read_command(p)                   &&
        ZERO_OR_MANY(read_optional_instructions(p))
    ) {
        return true;
    }

    p->cursor = tmp;

    return false;
}