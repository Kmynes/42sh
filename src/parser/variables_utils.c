#include "variables.h"

/**
 * \param char *key
 * \param char *value
 * \brief Initialize the first globale [key_value] 
*/
struct key_value *create_variable(char *key, char *value)
{
    struct key_value *v = malloc(sizeof(struct key_value));
    v->key = key;
    v->value = value;
    v->next = NULL;
    return v;
}


/**
 * \brief Free all globales [key_value]
 */
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

char *read_variable(char *arg)
{
    char *begin = arg;
    if (arg[0] == '$')
    {
        char *key = calloc(sizeof(char), strlen(arg));
        if (arg[1] == '{')
        {
            size_t i = 0;
            arg += 2;
            while (arg[i] != '}')
                i++;
            strncpy(key, arg, i);
        }
        else
            strcpy(key, arg + 1);
        struct key_value *kv = variables_get(key);
        free(key);

        if (kv)
            return kv->value;
    }

    return begin;
}