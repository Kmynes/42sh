#include "rules.h"

unsigned int nbr_section = 0;

bool read_sections(struct parser *p)
{
    int tmp = p->cursor;
    char capt_id[20];
    sprintf(capt_id, "id%d", nbr_section);
   
    if (read_spacing(p)                  &&
        parser_readchar(p, '[')          &&
        parser_begin_capture(p, capt_id) &&
        read_identifier(p)               &&
        parser_end_capture(p, capt_id)   &&
        parser_readchar(p, ']')          && 
        ONE_OR_MANY(read_key_value(p)))
    {
        struct ast_section *data = malloc(sizeof(struct ast_section));
        data->identifier = parser_get_capture(p, capt_id);
    
        struct ast_node *ast_section = ast_init();
        ast_section->type = AST_NODE_SECTION;
        ast_section->data = data;

        struct ast_node *ast_child_key_value = NULL;
        while ((ast_child_key_value = ast_get_from_parser(p, AST_NODE_KEY_VALUE)))
            ast_set_in_parent(ast_section, ast_child_key_value);

        ast_set_in_parser(p, ast_section);
        nbr_section++;
        return true;
    }

    p->cursor = tmp;
    return false;
}