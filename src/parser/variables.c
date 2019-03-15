#include "variables.h" 

struct key_value *variables = NULL;

void variables_init()
{
    variables = create_variable(NULL, NULL);
}

struct key_value *variables_add(char *key, char *value)
{
    if (variables == NULL)
        variables_init();

    if (variables->key == NULL)
    {
        variables->key = key;
        variables->value = value;
        return variables;
    }

    struct key_value *kv_exist = variables_update(key, value);
    if (kv_exist)
        return kv_exist;

    struct key_value *buff = variables;
    while (buff->next)
        buff = buff->next;

    buff->next = create_variable(key, value);

    return buff->next;
}

struct key_value *variables_get(char *key)
{
    if (strcmp(key, variables->key) == 0)
        return variables;

    struct key_value *buff = variables;
    struct key_value *found = NULL;

    while (buff && !found)
    {
        if (strcmp(key, buff->key) == 0)
            found = buff;

        buff = buff->next;
    }

    return found;
}

struct key_value *variables_update(char *key, char *value)
{
    struct key_value *kv = variables_get(key);
    if (kv)
    {
        free(kv->value);
        kv->value = value;
    }

    return kv;
}

void variables_delete(char *key)
{

    struct key_value *current = variables;
    struct key_value *next;
    if (strcmp(current->key, key) == 0)
    {
        next = variables->next;
        free(variables->key);
        free(variables->value);
        free(variables);
        variables = next;
        return;
    }

    next = current->next;

    while (current->next)
    {
        if (strcmp(next->key, key) == 0)
        {

            current->next = next->next;

            free(next->key);
            free(next->value);
            free(next);

            return;
        }

        current = next;
        next = current->next;
    }
}