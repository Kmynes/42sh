#include "parser/rules/rules.h"

bool read_ini_file(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(read_sections(p)) && parser_eof(p))
    {
        struct ast_node *ast = ast_ini_file_init();
        ast_recover_all_from_parser(ast, p, AST_NODE_SECTION);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

char *ast_ini_file_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "ini_file:");
}

struct ast_node *ast_ini_file_init(void)
{
    struct ast_node *ast = ast_init(AST_NODE_INI_FILE, NULL);
    ast->to_string = ast_ini_file_to_string;
    return ast;
}