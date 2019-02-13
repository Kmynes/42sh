#pragma once

enum token_type
{
    TOKEN_WORD
};

struct lexer
{
    struct token_list *tokens;
};

struct token
{
    char *str;
    enum token_type type;
};


struct lexer *lexer_init(void);
