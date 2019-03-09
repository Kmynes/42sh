#include <parser/rules/rules.h>

bool read_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    parser_begin_capture(p, "and_or_op");
    if ((parser_readtext(p, "&&") || parser_readtext(p, "||"))
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

bool read_and_or(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_pipeline(p))
    {
        struct ast_node *ast = ast_and_or_init();

        while (true)
        {
            struct ast_node *ast_pipeline = ast_get_from_parser(p, AST_PIPELINE);
            ast_set_in_parent(ast, ast_pipeline);
            if (!read_instructions(p)) {
                break;
            }

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

struct ast_node *ast_and_or_init()
{
    struct ast_node *ast = ast_init(AST_AND_OR, NULL);
    return ast;
}