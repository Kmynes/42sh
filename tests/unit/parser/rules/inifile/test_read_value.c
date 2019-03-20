#include "unit/parser/rules/test_rules.h"

void test_read_value(void)
{
    struct parser *p = parser_new_from_string("  toto");
    bool check = !read_value(p);
    print_state_test(check, "test_read_value (1)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_value (2)");
    parser_free(p);

    p = parser_new_from_string("toto  ");
    check = read_value(p);
    print_state_test(check, "test_read_value (3)");
    check = p->cursor == 4;
    print_state_test(check, "test_read_value (4)");
    parser_free(p);
}