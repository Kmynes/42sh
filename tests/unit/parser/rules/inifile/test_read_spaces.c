#include "unit/parser/rules/test_rules.h"

void test_read_spaces(void)
{
    struct parser *p = parser_new_from_string("toto=2");

    assert(read_spaces(p)); // validates even if nothing matches
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("  titi");

    assert(read_spaces(p));
    assert(p->cursor == 2);
    parser_free(p);
}