#include <string.h>
#include <parser/rules/rules.h>
#include <utils/string.h>

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

    while (*val != '\0' && (*val != ' ' && (c != '\\' && *val != '}')))
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

                    bool is_with_accolade = false;
                    char *var_name = get_variable_name(val, &val, len_value,
                        &is_with_accolade);

                    char *var_call = calloc(sizeof(char), strlen(var_name) + 3);

                    if (is_with_accolade)
                        sprintf(var_call, "${%s}", var_name);
                    else
                        sprintf(var_call, "$%s", var_name);

                    if (*val == '\0' || *val == ' ' || is_with_accolade)
                    {
                        struct key_value *kv = variables_get(var_name);
                        char *replacer = kv ? kv->value : "";
                        *addr = str_replace(var_call, replacer, *addr);
                        val = *addr;
                    }
                    free(var_name);
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
}