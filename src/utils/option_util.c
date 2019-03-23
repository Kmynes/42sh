#include <options.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execution/execute_command.h>
#include "function_utils.h"
#include "option_util.h"

int exec_file(char *file_name, bool ast_print_flag)
{
    char *content = get_content_file(file_name);
    int res = execute_command(content, ast_print_flag);
    free(content);

    return res;
}

bool stdin_has_input(void)
{
    fd_set readfds;
    FD_ZERO(&readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    FD_SET(STDIN_FILENO, &readfds);

    if (select(1, &readfds, NULL, NULL, &timeout))
        return true;

    return false;
}