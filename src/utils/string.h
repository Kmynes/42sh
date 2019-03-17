#pragma once
#include <string.h>

void string_list_free(char **list, size_t count);
char *str_replace(char *search, char *replace, char *subject);