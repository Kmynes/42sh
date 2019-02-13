#pragma once

#include <stddef.h>

#define MAX_OPTIONS 20

struct option
{
    char *name;
    char **params;
    size_t len_params;
};

struct list_options
{
    struct option *options;
    size_t len;
};

struct list_options *get_options(char **argv, int argc);

void free_options(struct list_options *options);
