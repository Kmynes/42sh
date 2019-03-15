#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        {
            void *ptr = realloc(buff, capacity *2);
            if (!ptr)
            {
                printf("Not enough memory");
                free(buff);
                exit(3);
            }
            capacity *= 2;
            buff = ptr;
        }

        strcat(buff, &c);
        nb_element++;
    }

    return buff;
}