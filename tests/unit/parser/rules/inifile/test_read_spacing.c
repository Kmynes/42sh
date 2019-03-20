#include "unit/parser/rules/test_rules.h"

void test_read_spacing(void)
{
    struct parser *p = parser_new_from_string("toto=2");

    bool check = !read_spacing(p);
    print_state_test(check, "test_read_spacing (1)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_spacing (2)");
    parser_free(p);

    p = parser_new_from_string(" \n");
    check = read_spacing(p);
    print_state_test(check, "test_read_spacing (3)");
    check = p->cursor == 2;
    print_state_test(check, "test_read_spacing (4)");
    parser_free(p);

    p = parser_new_from_string("; a\n");
    check = read_spacing(p);
    print_state_test(check, "test_read_spacing (5)");
    check = p->cursor == 4;
    print_state_test(check, "test_read_spacing (6)");
    parser_free(p);
}