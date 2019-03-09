#include <parser/rules/rules.h>

bool test_ZERO_OR_MANY_case_item(struct parser *p)
{
    while(parser_readchar(p, '|') && read_assignment_word(p));

    return true;
}

bool read_case_item(struct parser *p)
{
    unsigned int tmp = p->cursor;
    struct ast_case_item *data = malloc(sizeof(struct ast_case_item));
    data->words = malloc(sizeof(char*) * 16);
    data->nb_word = 1;
    data->capacity = 16;

    if (OPTIONAL(parser_readchar(p, '('))
        && parser_begin_capture(p, "case_item_0")
        && read_word(p)
        && parser_end_capture(p, "case_item_0")
	    && test_ZERO_OR_MANY_case_item(p)
	    && parser_readchar(p, ')')
	    && ZERO_OR_MANY(parser_readchar(p, '\n'))
	    && read_compound_list(p))
    {
	    struct ast_node *ast = ast_case_item_init();
	    ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);
	    ast_set_in_parser(p, ast);

        return true;
    }

    for (size_t i=1;i < data->nb_word; i++)
        free(data->words[i]);
    free(data->words);
    free(data);

    p->cursor = tmp;

    return false;
}

char *ast_case_item_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "case_item");
}

struct ast_node *ast_case_item_init(str)
{
    struct ast_node *ast = ast_init(AST_CASE_ITEM, NULL);
    ast->to_string = ast_case_item_to_string;
    return ast;
}