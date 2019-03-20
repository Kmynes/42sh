#include <parser/rules/rules.h>
/**
** \file read_do_group.c
** \brief reads do_group grammar as specified by the subject.
**
** do_group: 'do' compound_list 'done'
** \author Kevin
** \version 0.3
** \date March 2019
*/
bool read_do_group(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "do")
        && read_spaces(p)
        && read_compound_list(p)
        && read_spaces(p)
        && parser_readtext(p, "done"))
    {
        struct ast_node *ast = ast_do_group_init();

        struct ast_node *compound_list = ast_get_from_parser(p,
            AST_COMPOUND_LIST);
        ast_set_in_parent(ast, compound_list);

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