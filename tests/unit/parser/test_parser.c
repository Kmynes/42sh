//
// Created by thibault on 19/11/18.
//

#include <parser/parser.h>
#include "../test.h"

START_TEST(toto_test)
    {
        int status = parser_example();
        ck_assert(status == 42);
    }
END_TEST


struct TCase *test_parser(struct Suite *s)
{
    struct TCase *c = tcase_create("parser tests");
    suite_add_tcase(s, c);
    tcase_add_test(c, toto_test);

    return c;
}