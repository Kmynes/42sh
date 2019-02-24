#include "test_rules.h"

void test_parser_new_from_string()
{
    char *str = "toto";
    struct parser *parser = parser_new_from_string(str);
    assert(parser);
    assert(strcmp(parser->input, str) == 0);
    assert(parser->cursor == 0);
    parser_free(parser);
}

void test_read_key_value(void)
{
    test_parser_new_from_string();
}