#include "parser/rules/rules.h"

bool read_word(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ONE_OR_MANY(parser_readoutset(p, " \t\r\n\"'`|><;=&")))
        return 1;

//    // no quotes
//    if (ONE_OR_MANY(parser_readalphanum(p)))
//        return 1;

    p->cursor = tmp;

    // double quotes
    if (parser_readchar(p, '"') && ONE_OR_MANY(parser_readoutset(p, "\""))
        && parser_readchar(p, '"'))
        return 1;

    p->cursor = tmp;

    // single quotes
    if (parser_readchar(p, '\'') && ONE_OR_MANY(parser_readoutset(p, "'"))
        && parser_readchar(p, '\''))
        return 1;


    p->cursor = tmp;

    // back quotes
    if (parser_readchar(p, '`') && ONE_OR_MANY(parser_readoutset(p, "`"))
        && parser_readchar(p, '`'))
        return 1;

    p->cursor = tmp;
    return 0;
}