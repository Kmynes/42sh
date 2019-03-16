#include <parser/rules/rules.h>
/**
 * \file variables.c
 * Manages arguments sent by main and calls different parts of the code..
 * \author Kevin
 * \version 0.3
 * \date March 2019
 * \brief 
 */

struct key_value *variables = NULL;


/** 
 * \biref Initialize the globale variable [variables]
 * \return void.
 */
void variables_init()
{
    variables = create_variable(NULL, NULL);
}

/** 
 * \param char *key
 * \param char *value
 * \return struct key_value *.
 * \biref Add a variable to the liste of global variable
 */
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

/**
 * \param char *key
 * \brief Get a key value by his key
 * \return struct key_value *
 */
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

/**
 * \param char *key
 * \param char *value
 * \return struct key_value *
 * \brief Update a value by taking his key in parameter
 */
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

/**
 * \param char *key
 * \brief Delete a key_value from the list
 */
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