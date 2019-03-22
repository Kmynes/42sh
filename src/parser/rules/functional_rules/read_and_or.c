#include <parser/rules/rules.h>
/**
** \file read_and_or.c
** \brief reads and_or grammar as specified by the subject.
**
** and_or: pipeline (('&&'|'||') ('\n')* pipeline)*
** \author Kevin
** \version 0.3
** \date February 2019
*/

static bool read_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    parser_begin_capture(p, "and_or_op");
    if (read_spaces(p)
        && (parser_readtext(p, "&&") || parser_readtext(p, "||"))
        && read_spaces(p)
        && parser_end_capture(p, "and_or_op")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_pipeline(p))
    {
        return true;
    }

    parser_remove_capture_by_tag(p, "and_or_op");

    p->cursor = tmp;

    return false;
}

/**
** \param struct parser *p
** \brief Allow to read an [and_or] rule, return a [true]
*/
bool read_and_or(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(read_comment(p))
        && read_pipeline(p))
    {
        struct ast_node *ast = ast_and_or_init();
        while (true)
        {
            struct ast_node *ast_pipeline = ast_get_from_parser(p,
                AST_PIPELINE);
            ast_set_in_parent(ast, ast_pipeline);
            if (!read_instructions(p))
                break;

            char *op = parser_get_capture(p, "and_or_op");
            struct ast_node *ast_op = ast_word_init(op);
            ast_set_in_parent(ast, ast_op);
        }

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

int ast_and_or_exec(struct ast_node *ast)
{
    if (ast->type != AST_AND_OR)
        return 1;

    int res;
    for (size_t i = 0; ast->nb_children > i; i++)
    {
        res = ast->children[i]->exec(ast->children[i]);
        char *opp = NULL;
        if (i + 1 >= ast->nb_children)
            break;

        i++;
        opp = ast->children[i]->data;

        if (res == 0 && !strcmp(opp, "||"))
            i += 2;
        else if (res != 0 && !strcmp(opp, "&&"))
            i += 2;
    }

    return res;
}

struct ast_node *ast_and_or_init()
{
    struct ast_node *ast = ast_init(AST_AND_OR, NULL);
    ast->exec = ast_and_or_exec;
    return ast;
}