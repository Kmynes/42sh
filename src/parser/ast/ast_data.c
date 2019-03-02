#include <parser/parser.h>

void ast_assign_free(struct ast_assign *ast_assign)
{
    free(ast_assign->id);
    free(ast_assign->num);
    free(ast_assign);
}

void ast_key_value_free(struct ast_key_value *ast_key_value)
{
    free(ast_key_value->id);
    free(ast_key_value->value);
    free(ast_key_value);
}

void ast_section_free(struct ast_section *ast_sec)
{
    free(ast_sec->identifier);
    free(ast_sec);
}