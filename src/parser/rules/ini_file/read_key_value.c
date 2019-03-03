#include "parser/rules/rules.h"


bool read_key_value(struct parser *p)
{
    int tmp = p->cursor;

    if (read_spacing(p) &&
        parser_begin_capture(p, "key") && read_identifier(p) &&
        parser_end_capture(p, "key") &&
        read_spaces(p) &&
        parser_readchar(p, '=') &&
        read_spaces(p) &&
        parser_begin_capture(p, "value") && read_value(p) &&
        parser_end_capture(p, "value") &&
        read_spaces(p) &&
        read_end_of_line(p))
    {
        char *id = parser_get_capture(p, "key");
        char *value = parser_get_capture(p, "value");

        struct ast_key_value *data = malloc(sizeof(struct ast_key_value));
        data->id = id;
        data->value = value;

        struct ast_node *ast = ast_init(AST_NODE_KEY_VALUE, data);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

void ast_key_value_free(void *data)
{
    struct ast_key_value *ast_key_value = data;
    free(ast_key_value->id);
    free(ast_key_value->value);
    free(ast_key_value);
}
