#include <parser/rules/rules.h>
/**
** \file read_rule_until.c
** \brief reads rule_until grammar as specified by the subject.
**
** rule_until: 'until' compound_list do_group
** \author Daniel
** \version 0.3
** \date March 2019
*/
bool read_rule_until(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "until")
        && read_compound_list(p)
        && read_spaces(p)
        && read_do_group(p))
    {
        struct ast_node *ast = ast_rule_until_init();

        struct ast_node *compound_list = ast_get_from_parser(p,
            AST_COMPOUND_LIST);
        ast_set_in_parent(ast, compound_list);
        struct ast_node *do_group = ast_get_from_parser(p, AST_DO_GROUP);
        ast_set_in_parent(ast, do_group);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

int ast_rule_until_exec(struct ast_node *ast)
{
    if (ast->type != AST_RULE_UNTIL)
        return 1;

    int res;
    struct ast_node *compound_list = ast->children[0];
    struct ast_node *do_group = ast->children[1];
    while (compound_list->exec(compound_list) != 0)
        res = do_group->exec(do_group);

    return res;
}

struct ast_node *ast_rule_until_init()
{
    struct ast_node *ast = ast_init(AST_RULE_UNTIL, NULL);
    ast->exec = ast_rule_until_exec;
    return ast;
}