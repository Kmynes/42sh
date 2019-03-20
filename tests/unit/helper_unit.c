#include "helper_unit.h"

bool global_condition = true;

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

void print_state_test(bool condition, char *func_name)
{
    if (condition)
        printf("    %s:  \033[1;32mOK\033[0m\n", func_name);
    else
        printf("    %s:  \033[31mKO\033[0m\n", func_name);

    if (global_condition)
        global_condition = condition;
}