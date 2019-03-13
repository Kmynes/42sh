#include "parser/rules/rules.h"

bool read_word(struct parser *p)
{
    unsigned int tmp = p->cursor;

    char *protected_words[] =
    {
        "for",
        "while",
        "until",
        "case",
        "esac",
        "if",
        "then",
        "fi",
        "else",
        "elif",
        "do",
        "done",
        NULL
    };

    if (ONE_OR_MANY(parser_readoutset(p, " \t\r\n\"'`()|><;=&")))
    {
        for (size_t i = 0; protected_words[i] != NULL; i++)
        {
            size_t len = strlen(protected_words[i]);
            if (p->cursor - tmp == len && strncmp(p->input + tmp,
                protected_words[i], len) == 0)
                return false;
        }

        return true;
    }

    p->cursor = tmp;

    // double quotes
    if (parser_readchar(p, '"') && ONE_OR_MANY(parser_readoutset(p, "\""))
        && parser_readchar(p, '"'))
        return true;

    p->cursor = tmp;

    // single quotes
    if (parser_readchar(p, '\'') && ONE_OR_MANY(parser_readoutset(p, "'"))
        && parser_readchar(p, '\''))
        return true;


    p->cursor = tmp;

    // back quotes
    if (parser_readchar(p, '`') && ONE_OR_MANY(parser_readoutset(p, "`"))
        && parser_readchar(p, '`'))
        return true;

    p->cursor = tmp;
    return false;
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