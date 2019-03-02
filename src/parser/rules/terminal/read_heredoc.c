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
                struct ast_node *ast_section = ast_init(AST_NODE_HEREDOC,
                        parser_get_capture(p, "heredoc"));

                struct ast_node *ast_child_key_value = NULL;
                while ((ast_child_key_value = ast_get_from_parser(p, AST_NODE_KEY_VALUE)))
                    ast_set_in_parent(ast_section, ast_child_key_value);

                ast_set_in_parser(p, ast_section);
                return true;
            }
        }
    }

    p->cursor = tmp;
    return false;
}