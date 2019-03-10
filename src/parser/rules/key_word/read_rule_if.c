#include <parser/rules/rules.h>

bool read_rule_if(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "if")
        && read_compound_list(p)
        && parser_readtext(p, "then")
        && read_compound_list(p)
        && OPTIONAL(read_rule_else_clause(p))
        && parser_readtext(p, "fi"))
    {
        struct ast_node *ast = ast_rule_if_init();
        ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_rule_if_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "rule_if");
}

struct ast_node *ast_rule_if_init()
{
    struct ast_node *ast = ast_init(AST_RULE_IF, NULL);
    ast->to_string = ast_rule_if_to_string;
    return ast;
}