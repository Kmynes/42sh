#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int builtin_echo(char **args)
{
    if (args[0] == NULL)
        return 1;

    for (size_t i = 1; args[i]; i++)
        printf("%s\n", args[i]);

    return 0;
}