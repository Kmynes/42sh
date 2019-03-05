#include <parser/rules/rules.h>

static bool read_first_instructions(struct parser *p)
{
    int tmp = p->cursor;

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
    int tmp = p->cursor;
    bool is_word = false;

    if (
        (is_word = read_first_instructions(p)) ||
        read_redirection(p))
    {
        struct ast_node *ast = ast_init(AST_ELEMENT, NULL);
        if (is_word)
        {
            struct ast_element *data = malloc(sizeof(struct ast_element));
            data->elt = parser_get_capture(p, "elt");
            ast->data = data;
        }
        else
            ast_recover_all_from_parser(ast, p, AST_REDIRECTION);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}