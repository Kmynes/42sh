#include <parser/rules/rules.h>

static bool read_optional_instructions(struct parser *p)
{
    int tmp = p->cursor;

    if (parser_readchar(p, '|')                 &&
        ZERO_OR_MANY(parser_readchar(p, '\n'))  &&
        read_command(p)
    )
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_pipeline(struct parser *p)
{
    int tmp = p->cursor;

    struct ast_pipeline *data = malloc(sizeof(struct ast_pipeline));

    if (OPTIONAL((data->is_negative = parser_readchar(p, '!'))) &&
        read_command(p)                                         &&
        ZERO_OR_MANY(read_optional_instructions(p))
    ) {
        struct ast_node *ast = ast_init(AST_PIPELINE, data);
        struct ast_node *ast_child_command = NULL;

        while ((ast_child_command = ast_get_from_parser(p, AST_COMMAND)))
            ast_set_in_parent(ast, ast_child_command);

        ast_set_in_parser(p, ast);
        return true;
    }

    free(data);

    p->cursor = tmp;

    return false;
}