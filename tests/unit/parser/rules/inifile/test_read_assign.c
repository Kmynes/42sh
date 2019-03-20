#include "unit/parser/rules/test_rules.h"

void test_parser_readassign_ok(void)
{
    struct parser *p = parser_new_from_string("var=42; var=0");
    readassign(p);

    struct ast_node *ast = p->ast->children[0];
    char *s = ast->to_string(ast);
    bool check = strcmp(s, "assign_var_42") == 0;
    print_state_test(check, "test_parser_readassign_ok (1)");
    free(s);

    check = p->cursor == 6;
    print_state_test(check, "test_parser_readassign_ok (2)");
    parser_free(p);
}

void test_parser_readassign_nok(void)
{
    struct parser *p = parser_new_from_string("42=var");
    bool check = p->cursor == 0;
    print_state_test(check, "test_parser_readassign_nok");

    parser_free(p);
}

void test_read_assign(void)
{
    test_parser_readassign_ok();
    test_parser_readassign_nok();
}