#include "test_parser.h"

void test_parser_readtext()
{
    char *str = "Le chat est un félin";
    char *text = "est";

    size_t rank = 8;

    struct parser *parser = parser_new_from_string(str);

    parser->cursor = rank;

    assert(parser_readtext(parser, text));
    parser_free(parser);
}

void test_parser_readrange()
{
    char *str = "abc";
    struct parser *parser = parser_new_from_string(str);
    assert(parser_readrange(parser, 'a', 'z'));
    assert(parser->cursor == 1);
    assert(!parser_readrange(parser, 'A', 'Z'));
    assert(parser->cursor == 1);
    parser_free(parser);
}

void test_parser_readinset()
{
    struct parser *parser = parser_new_from_string("toto");
    assert(!parser_readinset(parser, "abcd"));
    assert(parser->cursor == 0);
    assert(parser_readinset(parser, "to"));
    assert(parser->cursor == 1);
    assert(!parser_readinset(parser, ""));
    assert(parser->cursor == 1);
    parser_free(parser);
}

void test_parser_readoutset()
{
    struct parser *parser = parser_new_from_string("toto");
    assert(parser_readoutset(parser, "abcd"));
    assert(parser->cursor == 1);
    assert(!parser_readoutset(parser, "o"));
    assert(parser->cursor == 1);
    assert(parser_readoutset(parser, ""));
    assert(parser->cursor == 2);
    parser_free(parser);
}

void test_parser_string_includes(void)
{
    test_parser_readtext();
    test_parser_readrange();
    test_parser_readinset();
    test_parser_readoutset();
}