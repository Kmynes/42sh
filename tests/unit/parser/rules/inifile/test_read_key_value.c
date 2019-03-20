#include "unit/parser/rules/test_rules.h"

void test_read_key_value(void)
{
    struct parser *p = parser_new_from_string("toto");
    bool check = !read_key_value(p);
    print_state_test(check, "test_read_key_value (1)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_key_value (2)");
    parser_free(p);

    p = parser_new_from_string("2toto=titi");
    check = !read_key_value(p);
    print_state_test(check, "test_read_key_value (3)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_key_value (4)");
    parser_free(p);

    p = parser_new_from_string("toto=titi");
    check = !read_key_value(p);
    print_state_test(check, "test_read_key_value (5)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_key_value (6)");
    parser_free(p);

    p = parser_new_from_string("; \ntoto=titi\n");

    check = read_key_value(p);
    print_state_test(check, "test_read_key_value (7)");

    struct ast_node *ast = p->ast->children[0];
    struct ast_key_value *data = (struct ast_key_value *) ast->data;

    check = strcmp(data->id, "toto") == 0;
    print_state_test(check, "test_read_key_value (8)");

    check = strcmp(data->value, "titi") == 0;
    print_state_test(check, "test_read_key_value (9)");

    check = p->cursor == 13;
    print_state_test(check, "test_read_key_value (10)");
    parser_free(p);
}