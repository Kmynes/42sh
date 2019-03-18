#include <parser/rules/rules.h>
/**
** \file read_rule_for.c
** \brief reads rule_for grammar as specified by the subject.
**
** rule_for:
** 'for' WORD ([';']|[('\n')* 'in' (WORD)* (';'|'\n')]) ('\n')* do_group
** \author Daniel + Kevin
** \version 0.3
** \date March 2019
*/
bool read_rule_for1_sub2(struct parser *p, struct ast_multiple_word *data)
{
    unsigned int tmp = p->cursor;
    if (read_multiple_word(p, data) && read_spaces(p))
    {
        return true;
    }
    p->cursor = tmp;
    return false;
}

bool read_rule_for1_sub(struct parser *p, struct ast_multiple_word *data)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_spaces(p)
        && parser_readtext(p, "in")
        && read_spaces(p)
        && ZERO_OR_MANY(read_rule_for1_sub2(p, data))
        && read_spaces(p)
        && (parser_readchar(p, ';') || parser_readchar(p, '\n'))
        && read_spaces(p))
    {
        return true;
    }

    p->cursor = tmp;
    return false;
}

bool read_rule_for1(struct parser *p, struct ast_multiple_word *data)
{
    unsigned int tmp = p->cursor;
    if (parser_readchar(p, ';')
        || read_rule_for1_sub(p, data))
    {
        return true;
    }

    p->cursor = tmp;

    return false;
}

bool read_rule_for(struct parser *p)
{
    unsigned int tmp = p->cursor;
    struct ast_multiple_word *data = malloc(sizeof(struct ast_multiple_word));
    data->words = malloc(sizeof(char*) * 16);
    data->nb_word = 1;
    data->capacity = 16;

    if (parser_readtext(p, "for")
        && read_spaces(p)
        && parser_begin_capture(p, "for_var_0")
        && read_word(p)
        && parser_end_capture(p, "for_var_0")
        && read_spaces(p)
        && OPTIONAL(read_rule_for1(p, data))
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_do_group(p))
    {
        data->words[0] = parser_get_capture(p, "for_var_0");
        struct ast_node *ast = ast_rule_for_init(data);

        if (data->nb_word > 1)
            variables_add(data->words[0], data->words[1]);

        ast_recover_all_from_parser(ast, p, AST_DO_GROUP);
        ast_set_in_parser(p, ast);
        return true;
    }

    for (size_t i=1;i < data->nb_word; i++)
        free(data->words[i]);
    free(data->words);
    free(data);

    p->cursor = tmp;
    return false;
}

void ast_rule_for_free(void *data)
{
    struct ast_multiple_word *ast_for = data;

    for (size_t i=0; i < ast_for->nb_word; i++)
        free(ast_for->words[i]);
    free(ast_for->words);
    free(ast_for);
}

char *ast_rule_for_to_string(struct ast_node *ast)
{
    char *str = malloc(sizeof(char) * 512);
    sprintf(str, "AST_RULE_FOR(%ld)", ast->nb_children);
    return str;
}

int ast_rule_for_exec(struct ast_node *ast)
{
    struct ast_multiple_word *data = ast->data;
    struct ast_node *first_child = ast->children[0];
    char *word = data->words[0];
    int res = 0;

    for (size_t i = 1; i < data->nb_word; i++)
    {
        variables_update(word, data->words[i]);
        res = first_child->exec(first_child);
    }

    return res;
}

struct ast_node *ast_rule_for_init(struct ast_multiple_word *data)
{
    struct ast_node *ast = ast_init(AST_RULE_FOR, data);

    ast->to_string = ast_rule_for_to_string;
    ast->free = ast_rule_for_free;
    ast->exec = ast_rule_for_exec;
    return ast;
}