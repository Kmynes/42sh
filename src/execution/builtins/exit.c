#include "../../parser/rules/rules.h"

int builtin_exit(char **voidarg)
{
    voidarg++;
    exit(0);
    return 0;
}