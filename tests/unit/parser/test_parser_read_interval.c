#include "test_parser.h"

void test_parser_readeol(void)
{
    char str[] = "philippe\nviens\r\nenc\0";
    struct parser *parser = parser_new_from_string(str);

    for (size_t i = 0 ; i < strlen(str) ; i++)
    {
        if(i == 8 || i == 14)
        {
            assert(parser_readeol(parser));
        }
        else
        {
            assert(!parser_readeol(parser));
            parser->cursor++;
        }
    }
    parser_free(parser);
}

void test_parser_readidentifier(void)
{
    struct parser *parser = parser_new_from_string("a_var titi");
    assert(parser_readidentifier(parser));
    assert(parser->cursor == 5);
    parser_free(parser);
    parser = parser_new_from_string(" a_var");
    assert(!parser_readidentifier(parser));
    assert(parser->cursor == 0);
    parser_free(parser);
}

void test_parser_readinteger(void)
{
    struct parser *parser = parser_new_from_string("123 456");
    assert(parser_readinteger(parser));
    assert(parser->cursor == 3);
    assert(!parser_readinteger(parser));
    assert(parser->cursor == 3);
    parser_free(parser);
}

void test_parser_read_interval(void)
{
    test_parser_readeol();
    test_parser_readidentifier();
    test_parser_readinteger();
}