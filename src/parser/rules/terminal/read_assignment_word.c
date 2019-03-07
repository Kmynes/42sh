#include <parser/rules/rules.h>

bool read_assignment_word(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_spaces(p) 
        && parser_begin_capture(p, "key")
        && read_identifier(p)
        && parser_end_capture(p, "key")
        && parser_readchar(p, '=')
        && parser_begin_capture(p, "value")
        && read_word(p)
        && parser_end_capture(p, "value"))
    {
        struct ast_assignment_word *data = malloc(sizeof(struct \
            ast_assignment_word));
        data->key = parser_get_capture(p, "key");
        data->value = parser_get_capture(p, "value");

        struct ast_node *ast = ast_assignment_word_init(data);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}

char *ast_assignment_word_to_string(struct ast_node *ast)
{
    char buff[512];
    struct ast_assignment_word *assign_word = ast->data;
    char *key = assign_word->key;
    char *value = assign_word->value;

    sprintf(buff, "assignment_word: -> key:%s value:%s", key, value);
    return strdup(buff);
}

void ast_assignment_word_free(void *data)
{
    struct ast_assignment_word *assign_word = data;
    free(assign_word->key);
    free(assign_word->value);
    free(assign_word);
}

struct ast_node *ast_assignment_word_init(struct ast_assignment_word *data)
{
    struct ast_node *ast = ast_init(AST_ASSIGNEMENT_WORD, data);
    ast->to_string = ast_assignment_word_to_string;
    ast->free = ast_assignment_word_free;
    return ast;
}