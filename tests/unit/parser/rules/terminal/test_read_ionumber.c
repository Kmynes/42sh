#include "unit/parser/rules/test_rules.h"

void test_read_ionumber(void)
{
    struct parser *p = parser_new_from_string("42 > toto");
    assert(read_ionumber(p));
    assert(p->cursor == 2);
    assert(!read_ionumber(p));
    parser_free(p);
}