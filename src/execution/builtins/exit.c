#include "../../parser/rules/rules.h"

bool builtin_exit(char *input)
{
    struct parser *p = parser_new_from_string(input);

    if (read_spaces(p) && parser_readtext(p, "exit") && read_spaces(p))
    {
        parser_free(p);
        exit(0);
    }

    parser_free(p);
    return false;
}
