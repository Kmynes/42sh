#include "unit/parser/rules/test_rules.h"

void test_read_heredoc(void)
{
    char *heredoc = "END\necho toto\nEND";
    struct parser *p = parser_new_from_string(heredoc);
    assert(read_heredoc(p));
    assert(p->cursor == (int)strlen(heredoc));
    struct ast_node *ast = p->ast->children[0];
    char *s = ast->to_string(ast);
    assert(strcmp(s, "heredoc_\necho toto\n") == 0);
    free(s);
    parser_free(p);

    p = parser_new_from_string("2_v=3");
    assert(!read_heredoc(p));
    assert(p->cursor == 0);
    parser_free(p);
}
