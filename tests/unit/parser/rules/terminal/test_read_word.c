#include "unit/parser/rules/test_rules.h"

void test_read_word_helper(char *input, char *expected)
{
    expected = expected ? expected : input;
    struct parser *p = parser_new_from_string(input);
    parser_begin_capture(p, "word");
    assert(read_word(p));
    parser_end_capture(p, "word");
    char *word = parser_get_capture(p, "word");
    assert(strcmp(word, expected) == 0);
    free(word);
    parser_free(p);
}

void test_read_word(void)
{
    test_read_word_helper("abc", NULL);
    test_not_rule(read_word, " abc");
    test_not_rule(read_word, "'abc");
    test_read_word_helper("'abc'", NULL);
    test_read_word_helper("`abc`", NULL);
    test_read_word_helper("`abc`", NULL);
    test_read_word_helper("`abc`", NULL);
    test_read_word_helper("toto=2", "toto");
    test_read_word_helper("toto>2", "toto");
    test_read_word_helper("toto<2", "toto");
    test_read_word_helper("toto;2", "toto");
    test_read_word_helper("toto||titi", "toto");
}