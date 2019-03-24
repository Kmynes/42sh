#include "parser.h"

bool parser_readalpha(struct parser *p)
{
    return parser_readrange(p, 'a', 'z');
}

bool parser_readnum(struct parser *p)
{
    return parser_readrange(p, '0', '9');
}

bool parser_readletter(struct parser *p)
{
    return parser_readrange(p, 'a', 'z')
        || parser_readrange(p, 'A', 'Z')
        || parser_readchar(p, '_');
}

bool parser_readalphanum(struct parser *p)
{
    return parser_readletter(p) || parser_readnum(p);
}