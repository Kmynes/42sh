#include <parser/parser.h>
#include <lexer/lexer.h>
#include "../test.h"

START_TEST(test_parse)
    {
        struct lexer *lexer = lexer_init();
        struct ast_node *ast = parse(lexer);
        ck_assert(ast != NULL);
    }
END_TEST


struct TCase *test_parser(struct Suite *s)
{
    struct TCase *c = tcase_create("parser tests");
    suite_add_tcase(s, c);
    tcase_add_test(c, test_parse);

    return c;
}