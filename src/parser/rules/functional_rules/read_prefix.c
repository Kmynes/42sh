#include <parser/rules/rules.h>
/**
** \file read_prefix.c
** \brief reads prefix grammar as specified by the subject.
**
** prefix: ASSIGMENT_WORD | redirection
** \author Thibault
** \version 0.3
** \date February 2019
*/
bool read_prefix(struct parser *p)
{
    unsigned int tmp = p->cursor;
    bool is_assign;
    read_spaces(p);
    if ((is_assign = read_assignment_word(p)) || read_redirection(p))
    {
        struct ast_node *ast = ast_prefix_init();

        if (is_assign)
            ast_recover_all_from_parser(ast, p, AST_ASSIGNEMENT_WORD);
        else
            ast_recover_all_from_parser(ast, p, AST_REDIRECTION);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

struct ast_node *ast_prefix_init()
{
    struct ast_node *ast = ast_init(AST_PREFIX, NULL);
    return ast;
}