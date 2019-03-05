#include "parser.h"

char *default_to_string(struct ast_node *ast, char *type)
{
    size_t output_capacity = 512;
    char *output = malloc(sizeof(char) * output_capacity);
    sprintf(output, "%s", type);

    size_t current_size = strlen(output);
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        char *child_str = child->to_string(child);

        current_size += strlen(child_str);

        if (current_size > output_capacity)
        {
            size_t new_size = sizeof(char) * output_capacity * 2;
            void *ptr = realloc(output, new_size);

            if (ptr == NULL)
                return output;

            output = ptr;
            output_capacity *=2;
        }

        sprintf(output, "\n\t- %s", child_str);
    }

    return output;
}