#include "options.h"
#include <stdlib.h>


// parse options as in myfind
struct list_options *get_options(char **argv, int argc)
{
    argv = 0;  // dummy
    argc = 0;  // dummy
    struct list_options *options = malloc(sizeof(struct list_options));
    options->len = 0;
    options->options = malloc(MAX_OPTIONS * (sizeof(struct option)));

    return options;
}