#include "parser/rules/rules.h"

unsigned int nbr_key_value = 0;

bool read_key_value(struct parser *p)
{
    int tmp = p->cursor;
    char capt_key[20];
    char capt_value[20];

    sprintf(capt_key, "key%d", nbr_key_value);
    sprintf(capt_value, "value%d", nbr_key_value);

    if (read_spacing(p) &&
        parser_begin_capture(p, capt_key) && read_identifier(p) &&
        parser_end_capture(p, capt_key) &&
        read_spaces(p) &&
        parser_readchar(p, '=') &&
        read_spaces(p) &&
        parser_begin_capture(p, capt_value) && read_value(p) &&
        parser_end_capture(p, capt_value) &&
        read_spaces(p) &&
        read_end_of_line(p))
    {
        char *id = parser_get_capture(p, capt_key);
        char *value = parser_get_capture(p, capt_value);

        struct ast_key_value *data = malloc(sizeof(struct ast_key_value));
        data->id = id;
        data->value = value;

        struct ast_node *ast = ast_init(AST_NODE_KEY_VALUE, data);

        ast_set_in_parser(p, ast);
        nbr_key_value++;
        return true;
    }

    p->cursor = tmp;
    return false;
}