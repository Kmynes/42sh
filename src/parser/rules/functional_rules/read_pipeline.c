#include <parser/rules/rules.h>

static bool read_optional_instructions(struct parser *p)
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
    char *buff = malloc(20);
    struct ast_pipeline *data = ast->data;
    sprintf(buff, "pipeline");
    if (data->is_negative)
    {
        strcat(buff, "_negative");
    }
    return buff;
}

void ast_pipeline_free(void *data)
{
    free(data);
}

struct ast_node *ast_pipeline_init(void *data)
{
    struct ast_node *ast = ast_init(AST_PIPELINE, data);
    ast->to_string = ast_pipeline_to_string;
    ast->free = ast_pipeline_free;
    return ast;
}