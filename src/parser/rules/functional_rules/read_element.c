#include <parser/rules/rules.h>
/**
** \file read_element.c
** \brief reads element grammar as specified by the subject.
**
** element: WORD | redirection
** \author Kevin
** \version 0.3
** \date February 2019
*/
bool read_element1(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_begin_capture(p, "elt")
        && read_word(p)
        && parser_end_capture(p, "elt"))
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
    read_spaces(p);
    if (read_redirection(p)
        || (is_word = read_element1(p)))
    {
        struct ast_node *ast = ast = ast_element_init();
        if (is_word)
        {
            struct ast_node *ast_word = ast_word_init(
                parser_get_capture(p, "elt"));
            ast_set_in_parent(ast, ast_word);
        }
        else
            ast_recover_all_from_parser(ast, p, AST_REDIRECTION);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

char *ast_element_to_string(struct ast_node *ast)
{
    // redirection stored in children
    struct ast_node *child = ast->children[0];
    if (child->type == AST_REDIRECTION)
        return strdup("AST_ELEMENT(1)");

    char buff[512];
    char *word = child->data;
    sprintf(buff, "AST_ELEMENT(1)_%s", word);
    return strdup(buff);
}

struct ast_node *ast_element_init()
{
    struct ast_node *ast = ast_init(AST_ELEMENT, NULL);
    ast->to_string = ast_element_to_string;
    return ast;
}