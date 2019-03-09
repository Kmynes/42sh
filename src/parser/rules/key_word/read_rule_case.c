#include <parser/rules/rules.h>

bool read_rule_case(struct parser *p)
{
    unsigned int tmp = p->cursor;
    struct ast_multiple_word *data = malloc(sizeof(struct ast_multiple_word));
    data->words = malloc(sizeof(char*) * 16);
    data->nb_word = 1;
    data->capacity = 16;

    if (parser_readtext(p, "case")
        && parser_begin_capture(p, "rule_case_0")
        && read_word(p)
        && parser_end_capture(p, "rule_case_0")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && parser_readtext(p, "in")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && OPTIONAL(read_case_clause(p))
        && parser_readtext(p, "esac"))
    {

        data->words[0] = parser_get_capture(p, "rule_case_0");
        struct ast_node *ast = ast_rule_case_init();
        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_rule_case_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "rule_case");
}

struct ast_node *ast_rule_case_init()
{
    struct ast_node *ast = ast_init(AST_RULE_CASE, NULL);
    ast->to_string = ast_rule_case_to_string;
    return ast;
}