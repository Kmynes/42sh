#include <parser/rules/rules.h>
/**
 * \file read_case_item.c
 * \brief reads case_item grammar as specified by the subject.
 *
 * case_item: ['('] WORD ('|' WORD)* ')' ('\n')* [ compound_list ]
 * \author Yann
 * \version 0.3
 * \date March 2019
 */
bool read_case_item_element(struct parser *p,
    struct ast_multiple_word *data)
{
    unsigned int tmp = p->cursor;

    if (parser_readchar(p, '|') && read_multiple_word(p, data))
        return true;

    p->cursor = tmp;
    return false;
}

bool read_case_item(struct parser *p)
{
    unsigned int tmp = p->cursor;
    struct ast_multiple_word *data = malloc(sizeof(struct ast_multiple_word));
    data->words = malloc(sizeof(char *) * 16);
    data->nb_word = 1;
    data->capacity = 16;

    if (OPTIONAL(parser_readchar(p, '('))
        && parser_begin_capture(p, "case_item_0")
        && read_word(p)
        && parser_end_capture(p, "case_item_0")
        && ZERO_OR_MANY(read_case_item_element(p, data))
        && parser_readchar(p, ')')
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && OPTIONAL(read_compound_list(p))
            )
    {

        data->words[0] = parser_get_capture(p, "case_item_0");
        struct ast_node *ast = ast_case_item_init(data);
        ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);
        ast_set_in_parser(p, ast);

        return true;
    }

    for (size_t i = 1; i < data->nb_word; i++)
        free(data->words[i]);
    free(data->words);
    free(data);

    p->cursor = tmp;

    return false;
}

void ast_case_item_free(void *data)
{
    struct ast_multiple_word *ast_for = data;

    for (size_t i = 0; i < ast_for->nb_word; i++)
        free(ast_for->words[i]);
    free(ast_for->words);
    free(ast_for);
}

int ast_case_item_exec(struct ast_node *ast)
{
    if (ast->type != AST_CASE_ITEM)
        return 1;

    if (ast->nb_children)
        return ast->children[0]->exec(ast->children[0]);

    return 0;
}

struct ast_node *ast_case_item_init(struct ast_multiple_word *data)
{
    struct ast_node *ast = ast_init(AST_CASE_ITEM, data);
    ast->free = ast_case_item_free;
    ast->exec = ast_case_item_exec;
    return ast;
}