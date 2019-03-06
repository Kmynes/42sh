#include "parser.h"

static void get_number(size_t *capacity, size_t len)
{
    while (*capacity < len)
        *capacity = *capacity * 2;
}

char *default_to_string(struct ast_node *ast, char *type)
{
    const char *separator = "\n\t- ";
    size_t size_separator = strlen(separator);
    size_t current_size = strlen(type);
    size_t output_capacity = 512;
    get_number(&output_capacity, current_size);

    char *output = calloc(sizeof(char), output_capacity);
    if (output == NULL)
        return NULL;

    sprintf(output, "%s", type);    
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        char *child_str = child->to_string(child);

        current_size += strlen(child_str) + size_separator;

        if (current_size > output_capacity)
        {
            size_t new_size = sizeof(char) * output_capacity * 2;
            void *ptr = realloc(output, new_size);

            if (ptr == NULL)
                return output;

            output = ptr;
            output_capacity *= 2;
        }

        strcat(output, separator);
        strcat(output, child_str);
        free(child_str);
    }

    output[current_size] = '\0';
    return output;
}