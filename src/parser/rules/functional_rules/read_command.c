#include <parser/rules/rules.h>
/**
** \file read_compound_list.c
** \brief reads compound_list grammar as specified by the subject.
**
** command: simple_command
** | shell_command (redirection)*
** | funcdec (redirection)*
** \author Thibault
** \version 0.3
** \date February 2019
*/
static bool read_second_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_shell_command(p) && ZERO_OR_MANY(read_redirection(p)))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

static bool read_third_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_funcdec(p) && ZERO_OR_MANY(read_redirection(p)))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

void set_ast_redirection(struct parser *p, struct ast_node *ast)
{
    ast_recover_all_from_parser(ast, p, AST_REDIRECTION);
}

bool read_command(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if ((read_simple_command(p)
        || read_second_instructions(p)
        || read_third_instructions(p))
        && ZERO_OR_MANY(read_comment(p)))
    {
        struct ast_node *ast = ast_command_init();
        struct ast_node *ast_child = NULL;


        ast_child = ast_get_from_parser(p, AST_SIMPLE_COMMAND);
        if (ast_child != NULL)
        {
            ast_set_in_parent(ast, ast_child);
            ast_set_in_parser(p, ast);
            return true;
        }

        ast_child = ast_get_from_parser(p, AST_SHELL_COMMAND);

        if (ast_child != NULL)
        {
            ast_set_in_parent(ast, ast_child);
            set_ast_redirection(p, ast);
            ast_set_in_parser(p, ast);
            return true;
        }

        ast_child = ast_get_from_parser(p, AST_FUNCDEC);
        ast_set_in_parent(ast, ast_child);
        set_ast_redirection(p, ast);
        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;
    return false;
}

int ast_command_exec(struct ast_node *ast)
{
     if (ast->type != AST_COMMAND)
        return 1;

    int res = 0;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        res = ast->children[i]->exec(ast->children[i]);

        if (res != 0)
            return res;
    }
    return res;
}

struct ast_node *ast_command_init()
{
    struct ast_node *ast = ast_init(AST_COMMAND, NULL);
    ast->exec = ast_command_exec;
    return ast;
}