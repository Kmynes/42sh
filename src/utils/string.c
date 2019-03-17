#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

void string_list_free(char **list, size_t count)
{
    for (size_t i = 0; i < count; i++)
        free(list[i]);
    free(list);
}

char *str_replace(char *search, char *replace, char *subject)
{
    size_t len_search = strlen(search);
    size_t len_replace = strlen(replace);
    size_t len_subject = strlen(subject);
    size_t len_newstr = len_replace + len_subject + 1;
    char *new_string = calloc(sizeof(char), len_newstr);
    bool search_found = false;
    char *tmp = subject;
    size_t cursor = 0;
    while (*subject)
    {
        if (!search_found && *subject == search[0])
        {
            char *buff_search = calloc(sizeof(char), len_search + 1);
            strncpy(buff_search, subject, len_search);
            if (strcmp(buff_search, search) == 0)
            {
                strcat(new_string, replace);
                cursor += len_replace;
                subject += len_search;
                search_found = true;
            }

            free(buff_search);
        }
        new_string[cursor++] = *subject;
        subject++;
    }

    free(tmp);
    return new_string;
}