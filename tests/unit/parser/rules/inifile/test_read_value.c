#include "unit/parser/rules/test_rules.h"

void test_read_value(void)
{
    struct parser *p = parser_new_from_string("  toto");
    assert(!read_value(p));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("toto  ");
    assert(read_value(p));
    assert(p->cursor == 4);
    parser_free(p);
}