#include "test_rules.h"

void test_read_spacing(void)
{
    struct parser *p = parser_new_from_string("toto=2");

    assert(!read_spacing(p));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string(" \n");
    assert(read_spacing(p));
    assert(p->cursor == 2);
    parser_free(p);

    p = parser_new_from_string("; a\n");
    assert(read_spacing(p));
    assert(p->cursor == 4);
    parser_free(p);
}