#include "test_parser.h"

void test_list_capt_lookup(void)
{
    struct capture_s capt = { 0, 2 };
    struct parser *p = parser_new_from_string("toto");
    p->capture = list_capt_store(p->capture, "id", &capt);
    bool check = list_capt_lookup(p->capture, "toto") == NULL;
    print_state_test(check, "test_list_capt_lookup (1)");

    struct capture_s *capture = list_capt_lookup(p->capture, "id");
    check = capture->begin == 0;
    print_state_test(check, "test_list_capt_lookup (2)");

    check = capture->end == 2;
    print_state_test(check, "test_list_capt_lookup (3)");

    parser_free(p);
}

void test_remove_capture_by_tag(void)
{
    struct capture_s capt = { 0, 2 };
    struct parser *p = parser_new_from_string("toto");
    p->capture = list_capt_store(p->capture, "id", &capt);
    // delete one
    parser_remove_capture_by_tag(p, "id");
    bool check = list_capt_lookup(p->capture, "id") == NULL;
    print_state_test(check, "test_remove_capture_by_tag (1)");

    // delete many
    p->capture = list_capt_store(p->capture, "id", &capt);
    p->capture = list_capt_store(p->capture, "id", &capt);
    parser_remove_capture_by_tag(p, "id");
    check = list_capt_lookup(p->capture, "id") == NULL;
    print_state_test(check, "test_remove_capture_by_tag (2)");

    parser_free(p);
}

void test_parser_capture(void)
{
    test_list_capt_lookup();
    test_remove_capture_by_tag();
}