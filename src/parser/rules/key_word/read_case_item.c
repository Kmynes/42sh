#include <parser/rules/rules.h>

bool test_ZERO_OR_MANY_case_item(struct parser *p)
{
    while(parser_readchar(p, '|') && read_assignment_word(p));

    return true;
}

bool read_case_item(struct parser *p)
{
    unsigned int tmp = p->cursor;
    
    if (OPTIONAL(parser_readchar(p, '('))
	&& read_assignment_word(p)
	&& test_ZERO_OR_MANY_case_item(p)
	&& parser_readchar(p, ')')
	&& ZERO_OR_MANY(parser_readchar(p, '\n'))
	&& read_compound_list(p)) {
        
	struct ast_node *ast = ast_case_item_init();

	ast_recover_all_from_parser(ast, p, AST_ASSIGNEMENT_WORD);
	//test 'ZERO_OR_MANY' de word pour recover ==> ast_recover_all_from_parser(ast, p, AST_ASSIGNMENT_WORD);
	ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);

	ast_set_in_parser(p, ast);
	
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_case_item_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "case_item");
}

struct ast_node *ast_case_item_init()
{
    struct ast_node *ast = ast_init(AST_CASE_ITEM, NULL);
    ast->to_string = ast_case_item_to_string;
    return ast;
}
