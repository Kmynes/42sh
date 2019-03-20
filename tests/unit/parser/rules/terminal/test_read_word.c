#include "unit/parser/rules/test_rules.h"

void test_read_word_helper(char *input, char *expected)
{
    expected = expected ? expected : input;
    struct parser *p = parser_new_from_string(input);
    parser_begin_capture(p, "word");
    bool check = read_word(p);
    print_state_test(check, "test_read_word_helper (1)");

    parser_end_capture(p, "word");
    char *word = parser_get_capture(p, "word");
    check = strcmp(word, expected) == 0;
    print_state_test(check, "test_read_word_helper (2)");

    free(word);
    parser_free(p);
}

void test_read_word(void)
{
    test_read_word_helper("abc", NULL);
    bool check = test_not_rule(read_word, " abc");
    print_state_test(check, "test_read_word (1)");
 
    // protected words
    check = test_not_rule(read_word, "for");
    print_state_test(check, "test_read_word (2)");

    check = test_not_rule(read_word, "else");
    print_state_test(check, "test_read_word (3)");

    check = test_not_rule(read_word, "fi");
    print_state_test(check, "test_read_word (4)");

    check = test_not_rule(read_word, "'abc");
    print_state_test(check, "test_read_word (5)");

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