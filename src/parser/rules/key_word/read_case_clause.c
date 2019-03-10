#include <parser/rules/rules.h>

bool test_ZERO_OR_MANY_case_clause(struct parser *p)
{
    while(parser_readtext(p, ";;") && ZERO_OR_MANY('\n') && read_case_item(p));

    return true;
}

bool read_case_clause(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_case_item(p)
        && test_ZERO_OR_MANY_case_clause(p)
	    && ZERO_OR_MANY(parser_readchar(p, '\n')))
    {
        struct ast_node *ast = ast_case_clause_init();

        ast_recover_all_from_parser(ast, p, AST_CASE_ITEM);

        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_case_clause_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "case_clause");
}

struct ast_node *ast_case_clause_init()
{
    struct ast_node *ast = ast_init(AST_CASE_CLAUSE, NULL);
    ast->to_string = ast_case_clause_to_string;
    return ast;
}