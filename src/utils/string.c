#include "string.h"

#include <stdlib.h>

void string_list_free(char **list, size_t count)
{
    for (size_t i = 0; i < count; i++)
        free(list[i]);
    free(list);
}
