#include "unit/parser/rules/test_rules.h"

void test_read_key_value(void)
{
    struct parser *p = parser_new_from_string("toto");
    assert(!read_key_value(p));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("2toto=titi");
    assert(!read_key_value(p));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("toto=titi");
    assert(!read_key_value(p));
    assert(p->cursor == 0);
    parser_free(p);

    p = parser_new_from_string("; \ntoto=titi\n");

    assert(read_key_value(p));

    struct ast_node *ast = p->ast->children[0];
    struct ast_key_value *data = (struct ast_key_value *) ast->data;
    assert(strcmp(data->id, "toto") == 0);
    assert(strcmp(data->value, "titi") == 0);    
    assert(p->cursor == 13);
    parser_free(p);
}