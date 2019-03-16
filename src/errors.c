#include <stdio.h>
#include <stdlib.h>

void error_ast_exec(char *function_name)
{
    char buffer[512];
    sprintf(buffer, "ast_exec_error in function %s", function_name);
    perror(buffer);
    exit(1);
}