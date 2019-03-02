#include "unit/parser/rules/test_rules.h"

void test_parser_readassign_ok(void)
{
    struct parser *p = parser_new_from_string("var=42; var=0");
    parser_readassign(p);
    char *id = parser_get_capture(p, "id");
    assert(strcmp(id, "var") == 0);
    free(id);
    char *num = parser_get_capture(p, "num");
    assert(strcmp(num, "42") == 0);
    free(num);
    assert(p->cursor == 6);
    parser_free(p);
}

void test_parser_readassign_nok(void)
{
    struct parser *p = parser_new_from_string("42=var");
    assert(!parser_get_capture(p, "id"));
    assert(!parser_get_capture(p, "num"));
    parser_readassign(p);
    assert(p->cursor == 0);
    parser_free(p);
}

void test_read_assign(void)
{
    test_parser_readassign_ok();
    test_parser_readassign_nok();
}