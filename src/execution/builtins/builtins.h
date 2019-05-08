#pragma once
#include <stddef.h>
#include "./42sh_history.h"

struct builtin {
    char *name;
    int (*func)(char **args);
};

int (*get_builtin(char *name))(char **args);

// builtins prototypes
int builtin_echo(char **args);
int builtin_cd(char **args);
int builtin_exit(char **voidarg);
int my_read_history(char **voidarg);