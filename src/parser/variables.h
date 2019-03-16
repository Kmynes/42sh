#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct key_value
{
    char *key;
    char *value;
    struct key_value *next;
};

extern struct key_value *variables;

void variables_init();
struct key_value *variables_add(char *key, char *value);
struct key_value *variables_get(char *key);
struct key_value *variables_update(char *key, char *value);
void variables_delete(char *key);

//Utils
struct key_value *create_variable(char *key, char *value);
void variables_free(void);
char *read_variable(char *arg);