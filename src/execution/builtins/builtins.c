#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "builtins.h"

extern struct builtin *builtin_table;

void builtin_table_init(void)
{
    struct builtin table[] = {
//            {"echo", builtin_echo},
            {NULL, NULL}
    };

    builtin_table = table;
}

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


