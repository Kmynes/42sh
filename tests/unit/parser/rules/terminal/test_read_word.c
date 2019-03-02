#include "unit/parser/rules/test_rules.h"

void test_read_word(void)
{
    struct parser *parser = parser_new_from_string("abc");
    assert(read_word(parser));
    assert(parser->cursor == 3);
    parser_free(parser);

    parser = parser_new_from_string(" abc");
    assert(!read_word(parser));
    assert(parser->cursor == 0);
    parser_free(parser);

    parser = parser_new_from_string("'abc");
    assert(!read_word(parser));
    assert(parser->cursor == 0);
    parser_free(parser);

    parser = parser_new_from_string("'abc'");
    assert(read_word(parser));
    assert(parser->cursor == 5);
    parser_free(parser);

    parser = parser_new_from_string("\"abc\"");
    assert(read_word(parser));
    assert(parser->cursor == 5);
    parser_free(parser);

    parser = parser_new_from_string("`abc`");
    assert(read_word(parser));
    assert(parser->cursor == 5);
    parser_free(parser);
}