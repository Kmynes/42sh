#include "unit/parser/rules/test_rules.h"

void test_read_eof(void)
{
    struct parser *p = parser_new_from_string("");
    assert(read_eof(p));
    assert(p->cursor == 0);
    parser_free(p);
}