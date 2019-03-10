#include <parser/rules/rules.h>

bool read_heredoc(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_begin_capture(p, "delimiter") && read_word(p)
        && parser_end_capture(p, "delimiter"))
    {
        char *delimiter = parser_get_capture(p, "delimiter");
        parser_begin_capture(p, "heredoc");
        while (p->input[p->cursor])
        {
            if (strcmp(p->input + p->cursor, delimiter) == 0)
            {
                parser_end_capture(p, "heredoc");
                char *heredoc = parser_get_capture(p, "heredoc");
                struct ast_node *ast = ast_heredoc_init(heredoc);

                ast_set_in_parser(p, ast);
                p->cursor += strlen(delimiter);
                free(delimiter);
                return true;
            }

            p->cursor++;
        }
        free(delimiter);
    }

    p->cursor = tmp;
    return false;
}

char *ast_heredoc_to_string(struct ast_node *ast)
{
    char *heredoc = ast->data;
    size_t size = strlen(heredoc) + strlen("hereodc_") + 1;
    char *output = malloc(size);
    sprintf(output, "heredoc_%s", heredoc);
    return output;
}

void ast_heredoc_free(void *data)
{
    free(data);
}

struct ast_node *ast_heredoc_init(void *data)
{
    struct ast_node *ast = ast_init(AST_HEREDOC, data);
    ast->to_string = ast_heredoc_to_string;
    ast->free = ast_heredoc_free;
    return ast;
}