#include <parser/rules/rules.h>
#include "execute_command.h"

int execute_command(char *command)
{
    struct parser *p = parser_new_from_string(command);

    if (!read_input(p))
    {
        printf("wrong input : %s\n", command);
        return 1;
    }

    struct ast_node *ast = p->ast->children[0];
    int res = ast->exec(ast);
    parser_free(p);
    return res;
}