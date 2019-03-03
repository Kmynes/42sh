#include "ast_print.h"
#include <parser/rules/rules.h>

struct ast_node_printer print_table[] = {
        { AST_NODE_ASSIGN, ast_assign_to_string },
        { 0, NULL }  // always last element
};

char *ast_node_to_string(struct ast_node *ast)
{
    struct ast_assign *data = ast->data;
    printf("data : %p\n", (void *)data);
    printf("strlen(num) : %d\n", (int) strlen(data->num));
    printf("num[0] --> %c\n", data->num[1]);
    printf("num --> %s\n", data->num);
    for (int i = 0; print_table[i].type; i++)
    {
        if (print_table[i].type == ast->type)
            return print_table[i].print_function(ast);
    }

    return NULL;
}

