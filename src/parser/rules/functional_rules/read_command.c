#include <parser/rules/rules.h>

static bool read_second_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_shell_command(p) && ZERO_OR_MANY(read_redirection(p)))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

static bool read_third_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_funcdec(p) && ZERO_OR_MANY(read_redirection(p)))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

static void set_ast_redirection(struct parser *p, struct ast_node *ast,
    struct ast_node *ast_child)
{
    ast_set_in_parent(ast, ast_child);
    ast_recover_all_from_parser(ast, p, AST_REDIRECTION);
}

bool read_command(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_simple_command(p)
        || read_second_instructions(p)
        || read_third_instructions(p))
    {
        struct ast_node *ast = ast_command_init();
        struct ast_node *ast_child = NULL;

        ast_child = ast_get_from_parser(p, AST_SIMPLE_COMMAND);
        ast_set_in_parser(p, ast);
        if (ast_child != NULL)
            return true;

        ast_child = ast_get_from_parser(p, AST_SHELL_COMMAND);

        if (ast_child != NULL)
        {
            set_ast_redirection(p, ast, ast_child);
            return true;
        }

        ast_child = ast_get_from_parser(p, AST_FUNCDEC);    
        set_ast_redirection(p, ast, ast_child);

        return true;
    }

    p->cursor = tmp;
    return false;
}

char *ast_command_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "read_command");
}

struct ast_node *ast_command_init()
{
    struct ast_node *ast = ast_init(AST_COMMAND, NULL);
    ast->to_string = ast_command_to_string;
    return ast;
}