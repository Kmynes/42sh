#include <parser/rules/rules.h>

static bool read_first_part(struct parser *p)
{
    int tmp = p->cursor;

    if ((parser_readchar(p, ';')  ||
        parser_readchar(p, '&')   ||
        parser_readchar(p, '\n'))              &&
        ZERO_OR_MANY(parser_readchar(p, '\n')) &&
        read_and_or(p)
    )
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

static bool read_second_part(struct parser *p)
{
    int tmp = p->cursor;

    if ((parser_readchar(p, '&') ||
         parser_readchar(p, ';') ||
         parser_readchar(p, '\n')) &&
        ZERO_OR_MANY(parser_readchar(p, '\n')))
    {
        return true;
    }

    p->cursor = tmp;
    return false;
}

bool read_compound_list(struct parser *p)
{
    int tmp = p->cursor;

    if (ZERO_OR_MANY(parser_readchar(p, '\n')) &&
        read_and_or(p)                        &&
        ZERO_OR_MANY(read_first_part(p))      &&
        read_second_part(p))) 
    {
        struct ast_node *ast = ast_init(AST_COMPOUND_LIST, NULL);
        struct ast_node *ast_child = NULL;

        while ((ast_child = ast_get_from_parser(p, AST_AND_OR)))
            ast_set_in_parent(ast, ast_child);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}