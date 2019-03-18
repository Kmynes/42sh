#include <options.h>
#include <execution/execute_command.h>
#include "function_utils.h"

int exec_file(char *file_name)
{
    char *content = get_content_file(file_name);
    int res = execute_command(content, 0);
    free(content);

    return res;
}