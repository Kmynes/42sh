#include <parser/rules/rules.h>

bool read_rule_case(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "case")
        && read_assignment_word(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && parser_readtext(p, "in")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && OPTIONAL(read_case_clause(p))
        && parser_readtext(p, "esac"))
    {

        struct ast_node *ast = ast_rule_case_init();

        ast_recover_all_from_parser(ast, p, AST_ASSIGNEMENT_WORD);

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