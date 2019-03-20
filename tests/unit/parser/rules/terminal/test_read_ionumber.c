#include "unit/parser/rules/test_rules.h"

void test_read_ionumber(void)
{
    struct parser *p = parser_new_from_string("42 > toto");
    bool check = read_ionumber(p);
    print_state_test(check, "test_read_ionumber (1)");

    check = p->cursor == 2;
    print_state_test(check, "test_read_ionumber (2)");
    check = !read_ionumber(p);
    print_state_test(check, "test_read_ionumber (3)");
    parser_free(p);
}