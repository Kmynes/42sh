#include "test_parser.h"

void test_parser_readtext(void)
{
    struct parser *parser = parser_new_from_string("toto est toto");
    bool check = parser_readtext(parser, "toto");
    print_state_test(check, "test_parser_readtext (1)");

    check = parser->cursor == 4;
    print_state_test(check, "test_parser_readtext (2)");
    parser_free(parser);

    parser = parser_new_from_string("est toto");
    check = !parser_readtext(parser, "toto");
    print_state_test(check, "test_parser_readtext (3)");

    check = parser->cursor == 0;
    print_state_test(check, "test_parser_readtext (4)");
    parser_free(parser);

    parser = parser_new_from_string(">>toto");
    check = parser_readtext(parser, ">>");
    print_state_test(check, "test_parser_readtext (5)");

    check = parser->cursor == 2;
    print_state_test(check, "test_parser_readtext (6)");
    parser_free(parser);
}

void test_parser_readrange(void)
{
    char *str = "abc";
    struct parser *parser = parser_new_from_string(str);
    bool check = parser_readrange(parser, 'a', 'z');
    print_state_test(check, "test_parser_readrange (1)");

    check = parser->cursor == 1;
    print_state_test(check, "test_parser_readrange (2)");

    check = !parser_readrange(parser, 'A', 'Z');
    print_state_test(check, "test_parser_readrange (3)");

    check = parser->cursor == 1;
    print_state_test(check, "test_parser_readrange (4)");
    parser_free(parser);
}

void test_parser_readinset(void)
{
    struct parser *parser = parser_new_from_string("toto");
    bool check = !parser_readinset(parser, "abcd");
    print_state_test(check, "test_parser_readinset (1)");

    check = parser->cursor == 0;
    print_state_test(check, "test_parser_readinset (2)");

    check = parser_readinset(parser, "to");
    print_state_test(check, "test_parser_readinset (3)");

    check = parser->cursor == 1;
    print_state_test(check, "test_parser_readinset (4)");

    check = !parser_readinset(parser, "");
    print_state_test(check, "test_parser_readinset (5)");

    check = parser->cursor == 1;
    print_state_test(check, "test_parser_readinset (6)");
    parser_free(parser);
}

void test_parser_readoutset(void)
{
    struct parser *p = parser_new_from_string("toto\n");
    bool check = parser_readoutset(p, "abcd");
    print_state_test(check, "test_parser_readoutset (1)"); 

    check = p->cursor == 1;
    print_state_test(check, "test_parser_readoutset (2)");

    check = !parser_readoutset(p, "o");
    print_state_test(check, "test_parser_readoutset (3)");

    check = p->cursor == 1;
    print_state_test(check, "test_parser_readoutset (4)");

    check = parser_readoutset(p, "");
    print_state_test(check, "test_parser_readoutset (5)");

    check = p->cursor == 2;
    print_state_test(check, "test_parser_readoutset (6)");

    p->cursor = 0;
    check = ZERO_OR_MANY(parser_readoutset(p, "\n"));
    print_state_test(check, "test_parser_readoutset (7)");

    check = p->cursor == 4;
    print_state_test(check, "test_parser_readoutset (8)");

    parser_free(p);
}

void test_parser_string_includes(void)
{
    test_parser_readtext();
    test_parser_readrange();
    test_parser_readinset();
    test_parser_readoutset();
}