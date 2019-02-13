#include <parser/parser.h>
#include <lexer/lexer.h>
#include <assert.h>
#include "../test.h"

void test_parse(void)
{
    struct lexer *lexer = lexer_init();
    struct ast_node *ast = parse(lexer);
    assert(ast != NULL);
}

void test_suite_parser(void)
{
    test_parse();
}
