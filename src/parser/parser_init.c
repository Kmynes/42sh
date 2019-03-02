#include "parser.h"

struct parser *parser_new_from_string(const char *text)
{
    struct parser *parser = malloc(sizeof(struct parser));
    size_t len = strlen(text);
    parser->input = malloc(len + 1);
    strcpy(parser->input, text);
    parser->cursor = 0;
    parser->capture = list_capt_init();
    parser->ast = ast_init(AST_NODE_EMPTY, NULL);
    parser->error = malloc(sizeof(struct error_s));

    return parser;
}

void parser_free(struct parser *p)
{
    if (p)
    {
        free(p->input);
        free_list_capt_s(p->capture);
        ast_free(p->ast);
        free(p->error);
        free(p);
    }
}