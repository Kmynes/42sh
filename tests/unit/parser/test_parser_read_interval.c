#include "test_parser.h"

void test_parser_readeol(void)
{
    char str[] = "philippe\nviens\r\nenc\0";
    struct parser *parser = parser_new_from_string(str);

    for (size_t i = 0 ; i < strlen(str) ; i++)
    {
        if (i == 8 || i == 14)
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

    bool check = parser_readidentifier(parser);
    print_state_test(check, "test_parser_readidentifier (1)");

    check = parser->cursor == 5;
    print_state_test(check, "test_parser_readidentifier (2)");

    parser_free(parser);
    parser = parser_new_from_string(" a_var");

    check = !parser_readidentifier(parser);
    print_state_test(check, "test_parser_readidentifier (3)");

    check = parser->cursor == 0;
    print_state_test(check, "test_parser_readidentifier (4)");
    parser_free(parser);
}

void test_parser_readinteger(void)
{
    struct parser *parser = parser_new_from_string("123 456");
    bool check = parser_readinteger(parser);
    print_state_test(check, "test_parser_readinteger (1)");

    check = parser->cursor == 3;
    print_state_test(check, "test_parser_readinteger (2)");

    check = !parser_readinteger(parser);
    print_state_test(check, "test_parser_readinteger (3)");

    check = parser->cursor == 3;
    print_state_test(check, "test_parser_readinteger (4)");
    parser_free(parser);
}

void test_parser_read_interval(void)
{
    test_parser_readeol();
    test_parser_readidentifier();
    test_parser_readinteger();
}