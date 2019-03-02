#include <parser/rules/rules.h>

bool read_ionumber(struct parser *p)
{
    return parser_readinteger(p);
}