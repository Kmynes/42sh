#include <parser/rules/rules.h>

bool read_funcdec(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "function")           &&
        parser_begin_capture(p, "func_n")        && 
        read_word(p)                             &&
        parser_end_capture(p, "func_n")          &&
        parser_readchar(p, '(')                  &&
        parser_readchar(p, ')')                  &&
        ZERO_OR_MANY(parser_readchar(p, '\n'))   &&
        read_shell_command(p)
    )
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

char *ast_funcdec_to_string(struct ast_node *ast)
{
    char buff[512];
    struct ast_funcdec *data = ast->data;
    char *func_name = data->function;
    sprintf(buff, "funcdec:\n\tfunction_name:%s", func_name);
    return default_to_string(ast, buff);
}

void ast_funcdec_free(void *data)
{
    struct ast_funcdec *funcdec = data;
    free(funcdec->function);
    free(funcdec);
}

struct ast_node *ast_funcdec_init(void *data)
{
    struct ast_node *ast = ast_init(AST_FUNCDEC, data);
    ast->to_string = ast_funcdec_to_string;
    ast->free = ast_funcdec_free;
    return ast;
}