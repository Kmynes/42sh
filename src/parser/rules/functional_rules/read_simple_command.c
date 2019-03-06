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
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);

        if (prefix_and_elements)
            ast_recover_all_from_parser(ast, p, AST_ELEMENT);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;   
}

char *ast_simple_command_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "simple_command:");
}

struct ast_node *ast_simple_command_init()
{
    struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
    ast->to_string =  ast_simple_command_to_string;
    return ast;
}