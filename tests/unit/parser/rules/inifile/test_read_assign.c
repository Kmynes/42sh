#include "unit/parser/rules/test_rules.h"

void test_parser_readassign_ok(void)
{
    struct parser *p = parser_new_from_string("var=42; var=0");
    readassign(p);

    struct ast_node *ast = p->ast->children[0];
    struct ast_assign *data = ast->data;
    printf("data : %p\n", (void *)data);
    printf("strlen(num) : %d\n", (int) strlen(data->num));
    printf("num <-- %s\n", data->num);
    char *s = ast_node_to_string(ast);
    printf("ast_node %s", s);
//    assert(strcmp(s, "assign_var_42") == 0);
    free(s);
    assert(p->cursor == 6);
    parser_free(p);
}

void test_parser_readassign_nok(void)
{
    struct parser *p = parser_new_from_string("42=var");
    assert(p->cursor == 0);
    parser_free(p);
}

void test_read_assign(void)
{
    test_parser_readassign_ok();
    test_parser_readassign_nok();
}