#include <parser/rules/rules.h>

static bool read_prefix_and_elements(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(read_prefix(p) && 
    ONE_OR_MANY(read_element(p))))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_simple_command(struct parser *p)
{
    unsigned int tmp = p->cursor;
    bool prefix_and_elements = false;
    if (ONE_OR_MANY(read_prefix(p)) ||
        (prefix_and_elements = read_prefix_and_elements(p)))
    {
        struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
        struct ast_node *ast_child = NULL;

        while ((ast_child = ast_get_from_parser(p, AST_PREFIX)))
            ast_set_in_parent(ast, ast_child);

        if (prefix_and_elements)
        {
            while ((ast_child = ast_get_from_parser(p, AST_ELEMENT)))
                ast_set_in_parent(ast, ast_child);
        }

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;   
}