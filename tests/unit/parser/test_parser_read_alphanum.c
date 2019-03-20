#include "test_parser.h"

void test_parser_readalpha(void)
{
    struct parser *parser = parser_new_from_string("e2");

    bool check = parser_readalpha(parser);
    print_state_test(check, "test_parser_readalpha (1)");

    check = !parser_readalpha(parser);
    print_state_test(check, "test_parser_readalpha (2)");
    parser_free(parser);
}

void test_parser_read_alphanum(void)
{
    test_parser_readalpha();
}