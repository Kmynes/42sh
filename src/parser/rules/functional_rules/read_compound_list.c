#include <parser/rules/rules.h>
/**
** \file read_compound_list.c
** \brief reads compound_list grammar as specified by the subject.
**
** compound_list:
** ('\n')* and_or ((';'|'&'|'\n') ('\n')* and_or)* [('&'|';'|'\n') ('\n')*]
** \author Kevin
** \version 0.3
** \date February 2019
*/
bool read_first_part(struct parser *p)
{
    unsigned int tmp = p->cursor;

    read_spaces(p);
    if ((parser_readchar(p, ';')
        || parser_readchar(p, '&')
        || parser_readchar(p, '\n'))
        && read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_and_or(p))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_second_part(struct parser *p)
{
    unsigned int tmp = p->cursor;

    read_spaces(p);
    if ((parser_readchar(p, '&')
        || parser_readchar(p, ';')
        || parser_readchar(p, '\n'))
        && ZERO_OR_MANY(parser_readchar(p, '\n')))
    {
        return true;
    }

    p->cursor = tmp;
    return false;
}

bool read_compound_list(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_and_or(p)
        && ZERO_OR_MANY(read_first_part(p))
        && OPTIONAL(read_second_part(p)))
    {
        struct ast_node *ast = ast_compound_list_init();

        ast_recover_all_from_parser(ast, p, AST_AND_OR);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

int ast_compound_list_exec(struct ast_node *ast)
{
    if (ast->nb_children == 1)
    {
        struct ast_node *first_child = ast->children[0];
        return first_child->exec(first_child);
    }
    else if (ast->nb_children > 1)
    {
        struct ast_node *child = NULL;
        int code = 0;
        for (size_t i = 0; i < ast->nb_children; i++)
        {
            child = ast->children[i];
            code = child->exec(child);
        }

        return code;
    }
    return 0;
}

struct ast_node *ast_compound_list_init()
{
    struct ast_node *ast = ast_init(AST_COMPOUND_LIST, NULL);
    ast->exec = ast_compound_list_exec;
    return ast;
}