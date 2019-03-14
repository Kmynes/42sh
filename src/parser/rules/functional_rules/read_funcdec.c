#include <parser/rules/rules.h>

bool read_funcdec(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "function")
        && read_spaces(p)
        && parser_begin_capture(p, "func_n")
        && read_word(p)
        && parser_end_capture(p, "func_n")
        && parser_readchar(p, '(')
        && parser_readchar(p, ')')
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_shell_command(p))
    {
        struct ast_funcdec *data = malloc(sizeof(struct ast_funcdec));
        data->function = parser_get_capture(p, "func_n");

        struct ast_node *ast = ast_funcdec_init(data);
        ast_recover_all_from_parser(ast, p, AST_SHELL_COMMAND);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

void ast_funcdec_free(void *data)
{
    struct ast_funcdec *funcdec = data;
    free(funcdec->function);
    free(funcdec);
}

int ast_funcdec_exec(struct ast_node *ast)
{
    if (ast->type != AST_FUNCDEC)
        error_ast_exec("ast_funcdec_exec");

    return ast->children[0]->exec(ast->children[0]);
}

struct ast_node *ast_funcdec_init(void *data)
{
    struct ast_node *ast = ast_init(AST_FUNCDEC, data);
    ast->free = ast_funcdec_free;
    ast->exec = ast_funcdec_exec;
    return ast;
}