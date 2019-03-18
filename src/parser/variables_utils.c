#include <string.h>
#include <parser/rules/rules.h>
#include <utils/string.h>
/**
** \file variables_utils.c
** \author Kevin
** \version 0.3
** \date March 2019
** \brief Useful function for variable management
*/

/**
** \param char *key
** \param char *value
** \brief Initialize the first global [key_value] 
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
** \brief Free all globals [key_value]
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

static void simple_variable(char **arg_ptr)
{
    char *arg = *arg_ptr;
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
        {
            free(*arg_ptr);
            *arg_ptr = strdup(kv->value);
        }
    }
}

static bool is_in_variable_pattern(char c)
{
    bool is_alpha = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    bool is_num = c >= '0' && c <= '9';
    return is_alpha || is_num || c == '_';
}

static char *take_of_quote(char *value, size_t len_value)
{
    char *val_replaced = calloc(sizeof(char), len_value);
    strncpy(val_replaced, value + 1, len_value - 2);
    free(value);
    return val_replaced;
}

static void check_simple_quote(char **addr, size_t len_value)
{
    char *value = *addr;
    if (value[0] == '\'' && value[len_value - 1] == '\'')
        *addr = take_of_quote(value, len_value);
}

static char *get_variable_name(char *val, char **store_val, size_t len_value,
    bool *is_with_accolade)
{
    size_t cursor = 0;
    char *capt = calloc(sizeof(char), len_value);
    char c = ' ';

    while (*val != '\0' && is_in_variable_pattern(*val))//(*val != ' ' && (c != '\\' && *val != '}')))
    {
        c = *val;
        capt[cursor++] = c;
        val++;
    }

    *store_val = val;
    *is_with_accolade = (c != '\\' && *val == '}');
    return capt;
}

static void check_quote(char **addr, size_t len_value)
{
    char *value = *addr;
    if (value[0] == '"' && value[len_value - 1] == '"')
    {
        *addr = take_of_quote(value, len_value);
        char *val = *addr;
        while (*val)
        {
            if (*val != '\\')
            {
                if (*val == '$')
                {
                    val += *(val + 1) == '{' ? 2 : 1;

                    bool is_accolade = false;
                    char *var_name = get_variable_name(val, &val, len_value,
                        &is_accolade);
                    struct key_value *kv = variables_get(var_name);
                    char *var_call = calloc(sizeof(char),
                        strlen(var_name) + 8);

                    sprintf(var_call, is_accolade ? "${%s}" : "$%s", var_name);
                    *addr = str_replace(var_call, kv ? kv->value : "", *addr);
                    val = *addr;
                    free(var_name);
                    free(var_call);
                }
            }
            val++;
        }
    }
}

void manage_variable_str(char **value)
{
    size_t len_value = strlen(*value);
    check_simple_quote(value, len_value);
    check_quote(value, len_value);
    simple_variable(value);
}