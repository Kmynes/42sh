#include "unit/parser/rules/test_rules.h"

void test_read_comment_simple(void)
{
    struct parser *p = parser_new_from_string(" #toto\n");
    assert(read_comment(p));
    assert(p->cursor == 7);
    parser_free(p);
}

void test_read_comment_multiline(void)
{
    struct parser *p = parser_new_from_string("#if echo ''; then\n#fi");
    assert(read_comment(p));
    parser_free(p);
}

void test_read_comment_fail(void)
{
    struct parser *p = parser_new_from_string(" #toto");
    assert(!read_assignment_word((p)));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("#toto");
    assert(!read_assignment_word((p)));
    assert(p->cursor == 0);
    parser_free(p);
}

void test_read_comment(void)
{
    test_read_comment_simple();
    test_read_comment_multiline();
    test_read_comment_fail();
}