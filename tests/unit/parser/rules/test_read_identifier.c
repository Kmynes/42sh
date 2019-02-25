#include "test_rules.h"

void test_read_identifier(void)
{
    struct parser *p = parser_new_from_string("a_var titi");
    assert(read_identifier(p));
    assert(p->cursor == 5);
    parser_free(p);
    p = parser_new_from_string(" a_var");
    assert(!read_identifier(p));
    assert(p->cursor == 0);
    parser_free(p);
}