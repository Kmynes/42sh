#include "unit/parser/rules/test_rules.h"

void test_read_eof(void)
{
    struct parser *p = parser_new_from_string("");
    bool check = read_eof(p);
    print_state_test(check, "test_read_eof (1)");

    check = p->cursor == 0;
    print_state_test(check, "test_read_eof (2)");
    parser_free(p);
}