#include "test_parser.h"

void test_parser_readtext(void)
{
    struct parser *parser = parser_new_from_string("toto est toto");
    assert(parser_readtext(parser, "toto"));
    assert(parser->cursor == 4);
    parser_free(parser);

    parser = parser_new_from_string("est toto");
    assert(!parser_readtext(parser, "toto"));
    assert(parser->cursor == 0);
    parser_free(parser);

    parser = parser_new_from_string(">>toto");
    assert(parser_readtext(parser, ">>"));
    assert(parser->cursor == 2);
    parser_free(parser);
}

void test_parser_readrange(void)
{
    char *str = "abc";
    struct parser *parser = parser_new_from_string(str);
    assert(parser_readrange(parser, 'a', 'z'));
    assert(parser->cursor == 1);
    assert(!parser_readrange(parser, 'A', 'Z'));
    assert(parser->cursor == 1);
    parser_free(parser);
}

void test_parser_readinset(void)
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

void test_parser_readoutset(void)
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