#include <parser/rules/rules.h>

bool read_rule_for(struct parser *p)
{
    unsigned int tmp = p->cursor;
    
    if (parser_readtext(p, "for")
        && parser_begin_capture(p, "for_var")
        && read_word(p)
        && parser_end_capture(p, "for_var")
        && (OPTIONAL(parser_readchar(p, ';'))
        || OPTIONAL(ZERO_OR_MANY(parser_readchar(p, '\n'))
        && parser_readtext(p, "in")
        && ZERO_OR_MANY(parser_begin_capture(p, "for_location")
        && read_word(p)
        && parser_end_capture(p, "for_location"))
        && (parser_readchar(p, ';') || parser_readchar(p, '\n'))))
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_do_group(p))
    {
        struct ast_node *ast = ast_rule_for_init();
        ast_recover_all_from_parser(ast, p, AST_DO_GROUP);
        ast_set_in_parser(p, ast);
        return true;
    }

    p->cursor = tmp;

    return false;
    
    return true;
}

char *ast_rule_for_to_string(struct ast_node *ast)
{
    return default_to_string(ast, "rule_for");
}

struct ast_node *ast_rule_for_init()
{
    struct ast_node *ast = ast_init(AST_RULE_FOR, NULL);
    ast->to_string = ast_rule_for_to_string;
    return ast;
}

