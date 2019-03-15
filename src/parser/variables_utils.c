#include "variables.h"

struct key_value *create_variable(char *key, char *value)
{
    struct key_value *v = malloc(sizeof(struct key_value));
    v->key = key;
    v->value = value;
    v->next = NULL;
    return v;
}

void variables_free(void)
{
    struct key_value *buff = NULL;
    while (variables)
    {
        buff = variables;
        variables = variables->next;

        free(buff->key);
        free(buff->value);
        free(buff);
    }
}