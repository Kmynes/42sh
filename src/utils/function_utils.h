#pragma once
#include <stddef.h>

void *enlarge_list(void *list, size_t *capacity);
char *get_content_file(const char *file_name);