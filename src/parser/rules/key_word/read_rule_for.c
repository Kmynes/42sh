#include <parser/rules/rules.h>

bool read_rule_for(struct parser *p)
{
    unsigned int tmp = p->cursor;
    /*
    if (parser_readtext(p, "for")
        && parser_begin_capture(p, "for_var")
        && read_word(p)
        && parser_end_capture(p, "for_var"))
        && (parser_readchar(p, ';')
        || )
        */
    if (true)
    {
        // Code the ast here
        return true;
    }

    p->cursor = tmp;

    return false;
}