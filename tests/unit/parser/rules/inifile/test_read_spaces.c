#include "unit/parser/rules/test_rules.h"

void test_read_spaces(void)
{
    struct parser *p = parser_new_from_string("toto=2");

    bool check = read_spaces(p); // validates even if nothing matches
    print_state_test(check, "test_read_spaces (1)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_spaces (2)");
    parser_free(p);

    p = parser_new_from_string("  titi");

    check = read_spaces(p);
    print_state_test(check, "test_read_spaces (3)");
    check = p->cursor == 2;
    print_state_test(check, "test_read_spaces (4)");
    parser_free(p);
}