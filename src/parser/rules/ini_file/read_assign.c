#include <parser/rules/rules.h>

bool readassign(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (parser_begin_capture(p, "id") && parser_readidentifier(p)
        && parser_end_capture(p, "id") && parser_readchar(p, '=')
        && parser_begin_capture(p, "num") && parser_readinteger(p) 
        && parser_end_capture(p, "num"))
    {
        struct ast_assign *data = malloc(sizeof(struct ast_assign));
        data->id = parser_get_capture(p, "id");
        data->num = parser_get_capture(p, "num");

        struct ast_node *ast = ast_assign_init(AST_NODE_ASSIGN, data);

        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;
    return false;
}

void ast_assign_free(void *data)
{
    struct ast_assign *ast_assign = data;
    free(ast_assign->id);
    free(ast_assign->num);
    free(data);
}

char *ast_assign_to_string(struct ast_node *ast)
{
    struct ast_assign *data = ast->data;
    size_t size = strlen(data->id) + strlen(data->num) + strlen("assign__") + 1;
    char *output = malloc(size);
    sprintf(output, "assign_%s_%s", data->id, data->num);
    return output;
}

struct ast_node *ast_assign_init(enum ast_node_type type, void *data)
{
    struct ast_node *ast = ast_init(type, data);
    ast->free = ast_assign_free;
    ast->to_string = ast_assign_to_string;

    return ast;
}