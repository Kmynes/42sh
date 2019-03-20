#include "test_parser.h"

void test_parser_eof(void)
{
    struct parser *parser = parser_new_from_string("");
    bool check = parser_eof(parser);
    print_state_test(check, "test_parser_eof (1)");
    parser_free(parser);

    parser = parser_new_from_string("abc");
    check = !parser_eof(parser);
    print_state_test(check, "test_parser_eof (2)");
    parser_free(parser);
}

void test_parser_getchar(void)
{
    char *str = "Le chat est un félin";
    struct parser *parser = parser_new_from_string(str);
    for (size_t i = 0; i < strlen(str); i++)
        assert(str[i] == parser_getchar(parser));

    parser_free(parser);
}

void test_parser_peekchar(void)
{
    char *str = "Le chat est un félyn";
    struct parser *parser = parser_new_from_string(str);
    char testChar = 'e';
    bool check = !parser_peekchar(parser, testChar);
    print_state_test(check, "test_parser_peekchar (1)");

    check = !parser_peekchar(parser, testChar);
    print_state_test(check, "test_parser_peekchar (2)");

    parser->cursor++;
    check = parser_peekchar(parser, testChar);
    print_state_test(check, "test_parser_peekchar (3)");
    parser_free(parser);
}

void test_parser_readchar(void)
{
    char *str = "boaisding";
    struct parser *parser = parser_new_from_string(str);
    bool check = parser_readchar(parser, 'b');
    print_state_test(check, "test_parser_readchar (1)");

    check = parser->cursor == 1;
    print_state_test(check, "test_parser_readchar (2)");

    check = !parser_readchar(parser, 'k');
    print_state_test(check, "test_parser_readchar (3)");

    check = parser_readchar(parser, 'o');
    print_state_test(check, "test_parser_readchar (4)");

    check = parser_readchar(parser, 'a');
    print_state_test(check, "test_parser_readchar (5)");

    check = !parser_readchar(parser, 'h');
    print_state_test(check, "test_parser_readchar (6)");

    check = parser_readchar(parser, 'i');
    print_state_test(check, "test_parser_readchar (7)");

    check = !parser_readchar(parser, 'z');
    print_state_test(check, "test_parser_readchar (8)");

    check = !parser_readchar(parser, 'u');
    print_state_test(check, "test_parser_readchar (9)");

    parser_free(parser);
}

void test_parser_character(void)
{
    test_parser_eof();
    test_parser_getchar();
    test_parser_peekchar();
    test_parser_readchar();
}