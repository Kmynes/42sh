#include "test_parser.h"

void test_list_capt_lookup()
{
    struct capture_s capt = { 0, 2 };
    struct parser *p = parser_new_from_string("toto");
    list_capt_store(p->capture, "id", &capt);
    assert(list_capt_lookup(p->capture, "toto") == NULL);
    struct capture_s *capture = list_capt_lookup(p->capture, "id");
    assert(capture->begin == 0);
    assert(capture->end == 2);

    parser_free(p);
}

void test_parser_readassign_ok()
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

void test_parser_readassign_nok()
{
    struct parser *p = parser_new_from_string("42=var");
    assert(!parser_get_capture(p, "id"));
    assert(!parser_get_capture(p, "num"));
    parser_readassign(p);
    assert(p->cursor == 0);
    parser_free(p);
}

void test_parser_capture(void)
{
    test_list_capt_lookup();
    test_parser_readassign_ok();
    test_parser_readassign_nok();
}