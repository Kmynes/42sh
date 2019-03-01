#include "test_parser.h"

void test_parser_eof(void)
{
    struct parser *parser = parser_new_from_string("");
    assert(parser_eof(parser));
    parser_free(parser);

    parser = parser_new_from_string("abc");
    assert(!parser_eof(parser));
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
    assert(!parser_peekchar(parser, testChar));
    assert(!parser_peekchar(parser, testChar));
    parser->cursor++;
    assert(parser_peekchar(parser, testChar));
    parser_free(parser);
}

void test_parser_readchar(void)
{
    char *str = "boaisding";
    struct parser *parser = parser_new_from_string(str);
    assert(parser_readchar(parser, 'b'));
    assert(parser->cursor == 1);
    assert(!parser_readchar(parser, 'k'));
    assert(parser_readchar(parser, 'o'));
    assert(parser_readchar(parser, 'a'));
    assert(!parser_readchar(parser, 'h'));
    assert(parser_readchar(parser, 'i'));
    assert(!parser_readchar(parser, 'z'));
    assert(!parser_readchar(parser, 'u'));
    parser_free(parser);
}

void test_parser_character(void)
{
    test_parser_eof();
    test_parser_getchar();
    test_parser_peekchar();
    test_parser_readchar();
}