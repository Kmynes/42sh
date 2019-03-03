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

void test_remove_capture_by_tag(void)
{
    struct capture_s capt = { 0, 2 };
    struct parser *p = parser_new_from_string("toto");
    list_capt_store(p->capture, "id", &capt);
    // delete one
    parser_remove_capture_by_tag(p, "id");
    assert(list_capt_lookup(p->capture, "id") == NULL);

    // delete many
    list_capt_store(p->capture, "id", &capt);
    list_capt_store(p->capture, "id", &capt);
    parser_remove_capture_by_tag(p, "id");
    assert(list_capt_lookup(p->capture, "id") == NULL);

    parser_free(p);
}

void test_parser_capture(void)
{
    test_list_capt_lookup();
    test_remove_capture_by_tag();
}