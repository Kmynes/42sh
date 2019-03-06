#include <parser/rules/rules.h>

static bool read_first_instructions(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_begin_capture(p, "elt") &&
        read_word(p)                &&
        parser_end_capture(p, "elt"))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_element(struct parser *p)
{
    unsigned int tmp = p->cursor;
    bool is_word = false;

    if ((is_word = read_first_instructions(p)) ||
        read_redirection(p))
    {
        struct ast_node *ast = NULL;
        if (is_word)
        {
            struct ast_element *data = malloc(sizeof(struct ast_element));
            data->elt = parser_get_capture(p, "elt");
            ast = ast_element_init(data);
        }
        else
        {
            ast = ast_element_init(NULL);
            ast_recover_all_from_parser(ast, p, AST_REDIRECTION);
        }

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_element_to_string(struct ast_node *ast)
{
    if (ast->data == NULL)
        return default_to_string(ast, "read_element");

    char buff[512];
    struct ast_element *data = ast->data;
    sprintf(buff, "read_element: -> element:%s", data->elt);
    return default_to_string(ast, buff); 
}

void ast_element_free(void *data)
{
    struct ast_element *ast_elt = data;
    free(ast_elt->elt);
    free(ast_elt);
}

struct ast_node *ast_element_init(struct ast_element *data)
{
    struct ast_node *ast = ast_init(AST_ELEMENT, data);
    ast->to_string = ast_element_to_string;
    if (data != NULL)
        ast->free = ast_element_free;
    return ast;
}