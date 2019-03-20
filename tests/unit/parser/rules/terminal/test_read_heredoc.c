#include "unit/parser/rules/test_rules.h"

void test_read_heredoc(void)
{
    char *heredoc = "END\necho toto\nEND";
    struct parser *p = parser_new_from_string(heredoc);
    bool check = read_heredoc(p);
    print_state_test(check, "test_read_heredoc (1)"); 
    check = p->cursor == strlen(heredoc);
    print_state_test(check, "test_read_heredoc (2)");

    struct ast_node *ast = p->ast->children[0];
    char *s = ast->to_string(ast);
    check = strcmp(s, "heredoc_\necho toto\n") == 0;
    print_state_test(check, "test_read_heredoc (3)");

    free(s);
    parser_free(p);

    p = parser_new_from_string("2_v=3");
    check = !read_heredoc(p);
    print_state_test(check, "test_read_heredoc (4)");
    check = p->cursor == 0;
    print_state_test(check, "test_read_heredoc (5)");
    parser_free(p);
}