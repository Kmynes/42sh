#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <lexer/lexer.h>

struct ast_node *parse(struct lexer *lexer)
{
    lexer = 0;  // NULL
    struct ast_node* ast = malloc(sizeof(struct ast_node));

    return ast;
}
