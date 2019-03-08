#include <parser/rules/rules.h>

bool read_case_clause(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (true) {
        // Code the ast here
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_case_clause_to_string(struct parser *p)
{
    return default_to_string(ast, "case_clause");
}

struct ast_node *ast_rule_while_init()
{
    struct ast_node *ast = ast_init(AST_CASE_CLAUSE, NULL);
    ast->to_string = ast_case_clause_to_string(NULL);
    return ast;
}
