#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int builtin_echo(char **args, size_t n)
{
    if (n == 0)
        return 1;

    printf("%s", args[0]);
    for (size_t i = 1; i < n; i++)
        printf("%s ", args[i]);

    return 0;
}