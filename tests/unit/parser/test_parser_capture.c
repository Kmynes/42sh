#include "test_parser.h"

void test_list_capt_lookup(void)
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

void test_parser_capture(void)
{
    test_list_capt_lookup();
}