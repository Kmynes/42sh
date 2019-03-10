#include <parser/rules/rules.h>

void set_ast_redirection(struct parser *p, struct ast_node *ast,
    struct ast_node *ast_child)
{
    ast_set_in_parent(ast, ast_child);
    ast_recover_all_from_parser(ast, p, AST_REDIRECTION);
}

bool read_command(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_simple_command(p))
    {
        struct ast_node *ast = ast_command_init();
        struct ast_node *ast_child = NULL;


        ast_child = ast_get_from_parser(p, AST_SIMPLE_COMMAND);
        if (ast_child != NULL)
        {
            ast_set_in_parent(ast, ast_child);
            ast_set_in_parser(p, ast);
            return true;
        }

        ast_child = ast_get_from_parser(p, AST_SHELL_COMMAND);

        if (ast_child != NULL)
        {
            ast_set_in_parent(ast, ast_child);
            set_ast_redirection(p, ast, ast_child);
            return true;
        }

        ast_child = ast_get_from_parser(p, AST_FUNCDEC);
        ast_set_in_parent(ast, ast_child);
        set_ast_redirection(p, ast, ast_child);

        return true;
    }

    p->cursor = tmp;
    return false;
}

int ast_command_exec(struct ast_node *ast)
{
     if (ast->type != AST_COMMAND)
        return 1;

    int res = 0;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        res = ast->children[i]->exec(ast->children[i]);

        if (res == 1)
            return 1;
    }
    return 0;
}

struct ast_node *ast_command_init()
{
    struct ast_node *ast = ast_init(AST_COMMAND, NULL);
    ast->exec = ast_command_exec;
    return ast;
}