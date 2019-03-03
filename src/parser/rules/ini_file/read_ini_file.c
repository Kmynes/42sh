#include "parser/rules/rules.h"

bool read_ini_file(struct parser *p)
{
    int tmp = p->cursor;

    if (ZERO_OR_MANY(read_sections(p)) && parser_eof(p))
    {
        struct ast_node *ast_ini_file = ast_init(AST_NODE_INI_FILE, NULL);

        struct ast_node *ast_child_section = NULL;

        while ((ast_child_section = ast_get_from_parser(p, AST_NODE_SECTION)))
            ast_set_in_parent(ast_ini_file, ast_child_section);

        ast_set_in_parser(p, ast_ini_file);
        return true;
    }

    p->cursor = tmp;
    return false;
}