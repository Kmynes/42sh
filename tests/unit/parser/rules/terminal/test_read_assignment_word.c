#include "unit/parser/rules/test_rules.h"

void test_read_assignment_word(void)
{
    struct parser *p = parser_new_from_string("var=42; var=0");
    assert(read_assignment_word(p));
    assert(p->cursor == 6);
    parser_free(p);

    p = parser_new_from_string("2_v=3");
    assert(!read_assignment_word((p)));
    assert(p->cursor == 0);
    parser_free(p);
}
