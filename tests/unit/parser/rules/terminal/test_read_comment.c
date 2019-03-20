#include "unit/parser/rules/test_rules.h"

void test_read_comment_simple(void)
{
    struct parser *p = parser_new_from_string(" #toto\n");
    bool check = read_comment(p);
    print_state_test(check, "test_read_comment_simple (1)");

    check = p->cursor == 7;
    print_state_test(check, "test_read_comment_simple (2)");
    parser_free(p);
}

void test_read_comment_multiline(void)
{
    struct parser *p = parser_new_from_string("#if echo ''; then\n#fi");
    bool check = read_comment(p);
    print_state_test(check, "test_read_comment_multiline");
    parser_free(p);
}

void test_read_comment_fail(void)
{
    struct parser *p = parser_new_from_string(" #toto");
    bool check = !read_assignment_word(p);
    print_state_test(check, "test_read_comment_fail (1)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_comment_fail (2)");
    parser_free(p);

    p = parser_new_from_string("#toto");
    check = !read_assignment_word(p);
    print_state_test(check, "test_read_comment_fail (3)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_comment_fail (4)");
    parser_free(p);
}

void test_read_comment(void)
{
    test_read_comment_simple();
    test_read_comment_multiline();
    test_read_comment_fail();
}