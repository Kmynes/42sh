#include "test_parser.h"

void test_parser_readalpha(void)
{
    struct parser *parser = parser_new_from_string("e2");
    assert(parser_readalpha(parser));
    assert(!parser_readalpha(parser));
    parser_free(parser);
}

void test_parser_read_alphanum(void)
{
    test_parser_readalpha();
}