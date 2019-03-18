#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function_utils.h"
/**
** \file function_utils.c
** \brief Collect a list of useful functions used in the project
**
** \author Kevin
** \version 0.3
** \date Marsh 2019
*/


void *enlarge_list(void *list, size_t *capacity)
{
    size_t new_capacity = (*capacity) * 2;
    void *ptr = realloc(list, new_capacity);
    if (!ptr)
    {
        free(list);
        printf("Not enough memory");
        exit(3);
        return NULL;
    }

    *capacity = new_capacity;
    return ptr;
}


char *get_content_file(const char *file_name)
{
    FILE *fp;
    fp = fopen(file_name, "r");
    if (!fp)
    {
        printf("Cannot open file: %s", file_name);
        exit(2);
        return NULL;
    }

    size_t capacity = 512;
    size_t nb_element = 0;
    char *buff = calloc(sizeof(char), capacity);

    char c;
    while ( (c = fgetc(fp)) != EOF)
    {
        if (nb_element == capacity)
            buff = enlarge_list(buff, &capacity);

        buff[nb_element++] = c;
    }
    buff[nb_element] = '\0';
    fclose(fp);

    return buff;
}