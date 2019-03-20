#include <options.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execution/execute_command.h>
#include "function_utils.h"
#include "option_util.h"

int exec_file(char *file_name)
{
    char *content = get_content_file(file_name);
    int res = execute_command(content, 0);
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