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
                struct ast_heredoc data = { parser_get_capture(p, "heredoc")};
                struct ast_node *ast = ast_init(AST_NODE_HEREDOC,
                        &data);

                ast_set_in_parser(p, ast);
                return true;
            }
        }
    }

    p->cursor = tmp;
    return false;
}