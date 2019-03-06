#include <parser/rules/rules.h>

bool read_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if ((parser_readtext(p, "&&") || parser_readtext(p, "||"))
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_pipeline(p))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_and_or(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_pipeline(p) && ZERO_OR_MANY(read_instructions(p)))
    {
        struct ast_node *ast = ast_and_or_init();

        ast_recover_all_from_parser(ast, p, AST_PIPELINE);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_and_or_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "and_or");
}

struct ast_node *ast_and_or_init()
{
    struct ast_node *ast = ast_init(AST_AND_OR, NULL);
    ast->to_string = ast_and_or_to_string;
    return ast;
}