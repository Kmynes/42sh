#include <parser/rules/rules.h>

bool read_rule_if(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (true) {
        // Code the ast here
        return true;
    }

    p->cursor = tmp;

    return false;
}