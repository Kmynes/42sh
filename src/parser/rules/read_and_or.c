#include <parser/rules/rules.h>

bool read_instructions(struct parser *p)
{
    int tmp = p->cursor;

    if ((parser_readtext(p, "&&") || parser_readtext(p, "||") ) &&
        ZERO_OR_MANY(parser_readchar(p, '\n'))                  &&
        read_pipeline(p))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_and_or(struct parser *p)
{
    int tmp = p->cursor;

    if (read_pipeline(p) && ZERO_OR_MANY(read_instructions(p)))
    {
        //Ajouter l'ast node read_and_or au parser
        return true;
    }

    p->cursor = tmp;

    return false;
}