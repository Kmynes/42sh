#include "builtins.h"

extern struct builtin *builtin_table;

void builtin_table_init(void)
{
    struct builtin table[] = {
            {"echo", builtin_echo}
    };

    builtin_table = table;
}

