#include <parser/rules/rules.h>

bool read_eof(struct parser *p)
{
    return p->cursor == strlen(p->input);
}