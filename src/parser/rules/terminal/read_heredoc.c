#include <parser/rules/rules.h>

bool read_heredoc(struct parser *p)
{
    int tmp = p->cursor;


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
                struct ast_node *ast = ast_heredoc_init(AST_NODE_HEREDOC,
                                                heredoc);

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
    int size = strlen(heredoc) + strlen("hereodc_") + 1;
    char *output = malloc(size);
    sprintf(output, "heredoc_%s", heredoc);
    return output;
}

struct ast_node *ast_heredoc_init(enum ast_node_type type, void *data)
{
    struct ast_node *ast = ast_init(type, data);
    ast->to_string = ast_heredoc_to_string;

    return ast;
}