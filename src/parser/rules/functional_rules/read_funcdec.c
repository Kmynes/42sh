#include <parser/rules/rules.h>

bool read_funcdec(struct parser *p)
{
    int tmp = p->cursor;

    if (parser_readtext(p, "function")        &&
        parser_begin_capture(p, "function_name") && 
        read_word(p)                          &&
        parser_end_capture(p, "function_name")   &&
        parser_readchar(p, '(')               &&
        parser_readchar(p, ')')               &&
        ZERO_OR_MANY(parser_readchar(p, '\n'))&&
        read_shell_command(p)
    )
    {
        struct ast_funcdec *data = malloc(sizeof(struct ast_funcdec));
        struct ast_node *ast = ast_init(AST_FUNCDEC, data);
        struct ast_node *ast_child = NULL;

        while ( (ast_child = ast_get_from_parser(p, AST_SHELL_COMMAND)) ) 
            ast_set_in_parent(ast, ast_child);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;  
}