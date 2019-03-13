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

int ast_do_group_exec(struct ast_node *ast)
{
    if (ast->type != AST_DO_GROUP)
        return 1;

    return ast->children[0]->exec(ast->children[0]);
}

struct ast_node *ast_do_group_init()
{
    struct ast_node *ast = ast_init(AST_DO_GROUP, NULL);
    ast->exec = ast_do_group_exec;
    return ast;
}