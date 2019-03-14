#pragma once

#include <stddef.h>

struct builtin {
    char *name;
    int (*func)(char **args, size_t n);
};

struct builtin *builtin_table;

void builtin_table_init(void);

// builtins prototypes
int builtin_echo(char **args, size_t n);
