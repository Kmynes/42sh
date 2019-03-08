#include <parser/rules/rules.h>

bool read_case_item(struct parser *p)
{
    //unsigned int tmp = p->cursor;
    return true;
}
/*
	WAITING FOR FINISHING TOUCH

    if (OPTIONAL(parser_readchar(p, '('))
	&& read_assignment_word(p)
	&& ZERO_OR_MANY(parser_readchar(p, '|') && read_assignmentt_word(p))
	&& parser_readchar(p, ')')
	&& ZERO_OR_MANY(parser_readchar(p, '\n'))
	&& read_compound_list(p)) {
        
	struct ast_node *ast = ast_case_item_init();

	ast_recover_all_from_parser(ast, p, );
	
        return true;
    }

    p->cursor = tmp;

    return false;
}

char *ast_case_item_to_string(struct parser *p)
{
    return default_to_string(ast, "case_item");
}

struct ast_node *ast_case_item_init()
{
    struct ast_node *ast = ast_init(AST_CASE_ITEM, NULL);
    ast->to_string = ast_case_item_to_string;
    return ast;
}
*/
