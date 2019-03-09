#include <parser/rules/rules.h>

static bool read_simple_command1(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (ONE_OR_MANY(read_prefix(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);

        if (ONE_OR_MANY(read_element(p)))
            ast_recover_all_from_parser(ast, p, AST_ELEMENT);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

static bool read_simple_command2(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(read_prefix(p)) && ONE_OR_MANY(read_element(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);

        ast_recover_all_from_parser(ast, p, AST_ELEMENT);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

bool read_simple_command(struct parser *p)
{
    return read_simple_command1(p) || read_simple_command2(p);
}

char *ast_simple_command_to_string(struct ast_node *ast)
{
    ast++;
    return strdup("simple_command");
}

struct ast_node *ast_simple_command_init()
{
    struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
    ast->to_string =  ast_simple_command_to_string;
    return ast;
}