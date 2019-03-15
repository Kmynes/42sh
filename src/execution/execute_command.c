#include <parser/rules/rules.h>
#include "execute_command.h"

int execute_command(char *command)
{
    struct parser *p = parser_new_from_string(command);
    do
    {
        if (!read_input(p))
        {
            printf("wrong input : %s\n", command);
            return 1;
        }
    }
    while (p->input[p->cursor]);

    struct ast_node *ast = NULL;
    int res = 0;

    for (size_t i = 0; i < p->ast->nb_children; i++)
    {
        ast = p->ast->children[i];
        res = ast->exec(ast);
    }

    parser_free(p);
    return res;
}