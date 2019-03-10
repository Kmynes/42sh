#include <parser/rules/rules.h>

bool read_do_group(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "do")
        && read_compound_list(p)
        && parser_readtext(p, "done"))
    {
        struct ast_node *ast = ast_do_group_init();

        ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_do_group_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "do_group");
}

struct ast_node *ast_do_group_init()
{
    struct ast_node *ast = ast_init(AST_RULE_UNTIL, NULL);
    ast->to_string = ast_do_group_to_string;
    return ast;
}