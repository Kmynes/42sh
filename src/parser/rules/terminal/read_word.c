#include "parser/rules/rules.h"

bool read_word(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ONE_OR_MANY(parser_readoutset(p, " \t\r\n\"'`()|><;=&")))
        return 1;

    p->cursor = tmp;

    // double quotes
    if (parser_readchar(p, '"') && ONE_OR_MANY(parser_readoutset(p, "\""))
        && parser_readchar(p, '"'))
        return 1;

    p->cursor = tmp;

    // single quotes
    if (parser_readchar(p, '\'') && ONE_OR_MANY(parser_readoutset(p, "'"))
        && parser_readchar(p, '\''))
        return 1;


    p->cursor = tmp;

    // back quotes
    if (parser_readchar(p, '`') && ONE_OR_MANY(parser_readoutset(p, "`"))
        && parser_readchar(p, '`'))
        return 1;

    p->cursor = tmp;
    return 0;
}

// useful sometimes we need a word as a child of an ast_node, like with and_or

void ast_word_free(void *data)
{
    free(data);
}

struct ast_node *ast_word_init(void *data)
{
    struct ast_node *ast = ast_init(AST_WORD, data);
    ast->free = ast_word_free;
    return ast;
}