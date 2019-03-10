#include <parser/rules/rules.h>

bool read_first_part(struct parser *p)
{
    unsigned int tmp = p->cursor;

    read_spaces(p);
    if ((parser_readchar(p, ';')
        || parser_readchar(p, '&')
        || parser_readchar(p, '\n'))
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
    if ((  parser_readchar(p, '&')
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

    if (ZERO_OR_MANY(parser_readchar(p, '\n'))
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

struct ast_node *ast_compound_list_init()
{
    struct ast_node *ast = ast_init(AST_COMPOUND_LIST, NULL);
    return ast;
}