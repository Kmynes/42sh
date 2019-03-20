#include "unit/parser/rules/test_rules.h"

void test_read_assignment_word(void)
{
    struct parser *p = parser_new_from_string("var=42; var=0");
    bool check = read_assignment_word(p);
    print_state_test(check, "test_read_assignment_word (1)");
    check = p->cursor == 6;
    print_state_test(check, "test_read_assignment_word (2)");
    parser_free(p);

    p = parser_new_from_string("2_v=3");
    check = !read_assignment_word(p);
    print_state_test(check, "test_read_assignment_word (3)");

    check = p->cursor == 0;
    print_state_test(check, "test_read_assignment_word (4)");
    parser_free(p);
}