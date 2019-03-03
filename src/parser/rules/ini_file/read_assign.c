#include <parser/rules/rules.h>

bool readassign(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (parser_begin_capture(p, "id") && parser_readidentifier(p)
        && parser_end_capture(p, "id") && parser_readchar(p, '=')
        && parser_begin_capture(p, "num") && parser_readinteger(p) 
        && parser_end_capture(p, "num"))
    {
        char *id = parser_get_capture(p, "id");
        char *num = parser_get_capture(p, "num");
        struct ast_assign *data = malloc(sizeof(struct ast_assign));
        data->id = id;
        data->num = num;

        struct ast_node *ast = ast_init(AST_NODE_ASSIGN, data);

        ast_set_in_parser(p, ast);
        //ast_store(p, AST_NODE_ASSIGN, &ast);

        return true;
    }

    p->cursor = tmp;
    return false;
}

char *readassign_to_string(struct ast_node *ast)
{
    struct ast_assign *data = (struct ast_assign *) ast->data;
    char *output = malloc(100);
    sprintf(output, "assign_%s_%s", data->id, data->num);
    return output;
}