#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "builtins.h"

struct builtin builtin_table[10] = {
        {
                "echo",
                builtin_echo
        },
        {
                "cd",
                builtin_cd
        },
        {
                "history",
                my_read_history
        },
        {
                "shopt",
                builtin_shopt
        },
        {
                NULL,
                NULL
        }
};

int (*get_builtin(char *name))(char **args)
{
    size_t i = 0;
    while (true)
    {
        struct builtin b = builtin_table[i];
        if (b.name == NULL)
            break;

        if (strcmp(b.name, name) == 0)
            return b.func;
        i++;
    }

    return NULL;
}