#include <parser/rules/rules.h>
/**
** \file read_pipeline.c
** \brief reads pipeline grammar as specified by the subject.
**
** pipeline: ['!'] command ('|' ('\n')* command)*
** \author Thibault
** \version 0.3
** \date February 2019
*/
bool read_optional_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readchar(p, '|')
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_command(p))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_pipeline(struct parser *p)
{
    unsigned int tmp = p->cursor;

    struct ast_pipeline *data = malloc(sizeof(struct ast_pipeline));
    data->is_negative = 0;

    if (OPTIONAL((data->is_negative = parser_readchar(p, '!')))
        && read_command(p)
        && ZERO_OR_MANY(read_optional_instructions(p)))
    {
        struct ast_node *ast = ast_pipeline_init(data);
        ast_recover_all_from_parser(ast, p, AST_COMMAND);
        ast_set_in_parser(p, ast);
        return true;
    }

    free(data);

    p->cursor = tmp;

    return false;
}

char *ast_pipeline_to_string(struct ast_node *ast)
{
    char *output = ast_node_default_to_string(ast);
    struct ast_pipeline *data = ast->data;
    if (data->is_negative)
        strcat(output, "_negative");
    return output;
}

void ast_pipeline_free(void *data)
{
    free(data);
}

int ast_pipeline_exec(struct ast_node *ast)
{
    if (ast->type != AST_PIPELINE)
        return 1;

    int res;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        res = ast->children[i]->exec(ast->children[i]);
    }

    struct ast_pipeline *data = ast->data;

    return data->is_negative ? !res: res;
}

struct ast_node *ast_pipeline_init(void *data)
{
    struct ast_node *ast = ast_init(AST_PIPELINE, data);
    ast->to_string = ast_pipeline_to_string;
    ast->free = ast_pipeline_free;
    ast->exec = ast_pipeline_exec;
    return ast;
}