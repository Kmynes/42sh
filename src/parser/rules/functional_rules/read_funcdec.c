#include <parser/rules/rules.h>
/**
** \file read_funcdec.c
** \brief reads funcdec grammar as specified by the subject.
**
** funcdec: ['function'] WORD '(' ')' ('\n')* shell_command
** \author Kevin
** \version 0.3
** \date February 2019
*/

struct list_func *functions = NULL;

static struct list_func *init_function(char *name,
    struct ast_node *ast_funcdec)
{
    struct list_func *func = malloc(sizeof(struct list_func));
    func->name = strdup(name);
    func->ast_funcdec = ast_funcdec;
    func->next = NULL;
    return func;
}

struct list_func *get_function(char *name)
{
    struct list_func *buff = functions;
    while (buff)
    {
        if (strcmp(buff->name, name) == 0)
            return buff;
        buff = buff->next;
    }

    return NULL;
}

struct list_func *add_function(char *name,
    struct ast_node *ast_funcdec)
{
    if (!functions)
    {
        functions = init_function(name, ast_funcdec);
        return functions;
    }

    struct list_func *buff = functions;
    while (buff->next)
    {
        if (strcmp(name, buff->name) == 0)
        {
            buff->ast_funcdec = ast_funcdec;
            return buff;
        }
        buff = buff->next;
    }

    buff->next = init_function(name, ast_funcdec);
    return buff->next;
}

void free_functions(void)
{
    struct list_func *buff = functions;
    while (buff)
    {
        free(buff->name);
        buff = functions->next;

        free(functions);
        functions = buff;
    }
}

bool read_funcdec(struct parser *p)
{
    unsigned int tmp = p->cursor;
    read_spaces(p);
    if (OPTIONAL(parser_readtext(p, "function"))
        && read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && parser_begin_capture(p, "func_n")
        && read_word(p)
        && parser_end_capture(p, "func_n")
        && read_spaces(p)
        && parser_readchar(p, '(')
        && parser_readchar(p, ')')
        && read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n')))
    {
        struct ast_funcdec *data = malloc(sizeof(struct ast_funcdec));
        data->function = parser_get_capture(p, "func_n");

        if (read_shell_command(p))
        {
            struct ast_node *ast = ast_funcdec_init(data);
            ast_recover_all_from_parser(ast, p, AST_SHELL_COMMAND);
            add_function(data->function, ast);
            ast_set_in_parser(p, ast);
            return true;
        }
        else
        {
            free(data->function);
            free(data);
            p->cursor = tmp;
            return false;
        }
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

    struct ast_node *first_child = ast->children[0];
    return first_child->exec(first_child);
}

char *ast_funcdec_to_string(struct ast_node *ast)
{
    char *str = calloc(sizeof(char), 512);
    sprintf(str, "AST_FUNCDEC(%ld)", ast->nb_children);
    return str;
}

struct ast_node *ast_funcdec_init(void *data)
{
    struct ast_node *ast = ast_init(AST_FUNCDEC, data);
    ast->free = ast_funcdec_free;
    ast->exec = ast_funcdec_exec;
    ast->to_string = ast_funcdec_to_string;
    return ast;
}