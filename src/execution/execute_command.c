#include <parser/rules/rules.h>
#include <ast_print.h>
#include <options.h>
#include <interactive/prompt.h>
#include <utils/option_util.h>
#include "execute_command.h"

int execute_command(char *command, int ast_print_flag)
{
    struct parser *p = parser_new_from_string(command);
    do
    {
        if (!read_input(p))
        {
            fprintf(stderr, "wrong input : %s\n", command);
            parser_free(p);
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
        fflush(stdout);
    }

    if (ast_print_flag)
        ast_print(p->ast, NULL);

    parser_free(p);
    return res;
}

int execute_shell_no_option(int ast_print_flag)
{
    if (stdin_has_input())
    {
        char buf[MAX_INPUT];

        fgets(buf, sizeof buf, stdin);
        int status = execute_command(buf, ast_print_flag);
        if (status == 1)
            return 2;
        else
            return status;
    }
    else
    {
        create_prompt();
        return 0;
    }
}