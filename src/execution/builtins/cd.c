#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int builtin_cd(char **args)
{
    if (args[0] == NULL)
        return 1;

    return chdir(args[0]);
}