#include <parser/rules/rules.h>
/**
** \file read_input.c
** \brief reads input grammar as specified by the subject.
**
** input: list '\n' | list EOF | '\n' | EOF
** \author Kevin
** \version 0.3
** \date February 2019
*/

bool read_input1(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_list(p))
    {
        //# put this back sometime
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_input2(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_list(p) && read_eof(p))
        return true;

    p->cursor = tmp;

    return false;
}

/**
** \param struct parser *p
** \return bool
** \brief Allow to read an input and store this ast in the parser's children
*/
bool read_input(struct parser *p)
{
    unsigned int tmp = p->cursor;
    bool has_list;

    if ((has_list = read_input1(p))
        || (has_list = read_input2(p))
        || parser_readchar(p, '\n')
        || ONE_OR_MANY(read_comment(p))
        || read_eof(p))
    {
        struct ast_node *ast = ast_input_init();

        if (has_list)
        {
            struct ast_node *ast_child = ast_get_from_parser(p, AST_LIST);
            ast_set_in_parent(ast, ast_child);
        }

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

int ast_input_exec(struct ast_node *ast)
{
    if (ast->type != AST_INPUT)
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

struct ast_node *ast_input_init(void)
{
    struct ast_node *ast = ast_init(AST_INPUT, NULL);
    ast->exec = ast_input_exec;
    return ast;
}