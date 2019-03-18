#include "helper_unit.h"

void execute_sh_test_files(const char *path)
{
    char *input = get_content_file(path);
    struct parser *p = parser_new_from_string(input);
    do
    {
        if (!read_input(p))
        {
            printf("wrong input : %s\n", input);
            return;
        }
    }
    while (p->input[p->cursor]);

    struct ast_node *ast = NULL;
    for (size_t i = 0; i < p->ast->nb_children; i++)
    {
        ast = p->ast->children[i];
        ast->exec(ast);
    }

    parser_free(p);
    free(input);
}