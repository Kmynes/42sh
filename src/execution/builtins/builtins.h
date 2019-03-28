#pragma once

#include <stddef.h>

struct builtin {
    char *name;
    int (*func)(char **args);
};

int (*get_builtin(char *name))(char **args);


// builtins prototypes
int builtin_echo(char **args);
int builtin_exit(char *input);
