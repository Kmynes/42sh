#include <parser/rules/rules.h>

bool read_rule_case(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (true) {
        // Code the ast here
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_rule_case_to_string(struct parseur *p)
{
    return default_to_string(ast, "rule_case");
}

struct ast_node *ast_rule_case_init()
{
    struct ast_node *ast = ast_init(AST_RULE_CASE, NULL);
    ast->tostring = ast_rule_case_to_string(NULL);
    return ast;
}
