#include <parser/rules/rules.h>

bool read_rule_until(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "until")
        && read_compound_list(p)
        && read_do_group(p))
    {
        struct ast_node *ast = ast_rule_until_init();

        ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);
        ast_recover_all_from_parser(ast, p, AST_DO_GROUP);

        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_rule_until_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "rule_until");
}

struct ast_node *ast_rule_until_init()
{
    struct ast_node *ast = ast_init(AST_RULE_UNTIL, NULL);
    ast->to_string = ast_rule_until_to_string;
    return ast;
}