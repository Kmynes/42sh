#pragma once

#include <stddef.h>

struct builtin {
    char *name;
    int (*func)(char **args);
};

struct builtin *builtin_table;

void builtin_table_init(void);
int (*get_builtin(char *name))(char **args);


// builtins prototypes
int builtin_echo(char **args);
