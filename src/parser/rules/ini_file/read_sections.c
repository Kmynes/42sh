#include "parser/rules/rules.h"

bool read_sections(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_spacing(p)
        && parser_readchar(p, '[')
        && parser_begin_capture(p, "id")
        && read_identifier(p)
        && parser_end_capture(p, "id")
        && parser_readchar(p, ']')
        && ONE_OR_MANY(read_key_value(p)))
    {
        struct ast_section *data = malloc(sizeof(struct ast_section));
        data->identifier = parser_get_capture(p, "id");

        struct ast_node *ast = ast_section_init(data);
        ast_recover_all_from_parser(ast, p, AST_NODE_KEY_VALUE);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

void ast_section_free(void *data)
{
    struct ast_section *ast_sec = data;
    free(ast_sec->identifier);
    free(ast_sec);
}

struct ast_node *ast_section_init(struct ast_section *data)
{
    struct ast_node *ast = ast_init(AST_NODE_SECTION, data);
    ast->free = ast_section_free;
    ast->to_string = NULL;

    return ast;
}
