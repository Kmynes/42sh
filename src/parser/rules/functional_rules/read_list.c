#include <parser/rules/rules.h>

static bool read_list1(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if ((parser_readchar(p, ';') ||
          parser_readchar(p, '&'))   &&
          read_and_or(p))
    {
        return true;
    }

    p->cursor =tmp;

    return false;
}

bool read_list(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_and_or(p)           &&
        ZERO_OR_MANY(read_list1(p)) &&
        (parser_readchar(p, ';') || 
        parser_readchar(p, '&')))
    {
        struct ast_node *ast = ast_list_init();
        ast_recover_all_from_parser(ast, p, AST_AND_OR);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_list_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "list");
}

struct ast_node *ast_list_init()
{
    struct ast_node *ast = ast_init(AST_LIST, NULL);
    ast->to_string = ast_list_to_string;
    return ast;
}