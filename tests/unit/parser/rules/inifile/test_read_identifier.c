#include "unit/parser/rules/test_rules.h"

void test_read_identifier(void)
{
    struct parser *p = parser_new_from_string("a_var titi");
    bool check = read_identifier(p);
    print_state_test(check, "test_read_identifier (1)");

    check = p->cursor == 5;
    print_state_test(check, "test_read_identifier (2)");
    parser_free(p);

    p = parser_new_from_string(" a_var");
    check = !read_identifier(p);
    print_state_test(check, "test_read_identifier (3)");

    check = p->cursor == 0;
    print_state_test(check, "test_read_identifier (4)");
    parser_free(p);
}