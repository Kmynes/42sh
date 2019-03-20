#include <parser/rules/rules.h>
/**
** \file read_rule_if.c
** \brief reads rule_if grammar as specified by the subject.
**
** rule_if: 'if' compound_list 'then' compound_list [else_clause] 'fi'
** \author Daniel + Kevin
** \version 0.3
** \date March 2019
*/

/**
** \param struct parser *p
** \return bool
** \brief Create a rule if with all his childs
** and return true if this rule is respected.
*/
bool read_rule_if(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, "if")
        && read_spaces(p)
        && read_compound_list(p)
        && read_spaces(p)
        && parser_readtext(p, "then")
        && read_spaces(p)
        && read_compound_list(p))
    {
        struct ast_node *ast = ast_rule_if_init();
        ast_recover_all_from_parser(ast, p, AST_COMPOUND_LIST);

        if (OPTIONAL(read_else_clause(p))
            && parser_readtext(p, "fi"))
        {
            ast_recover_all_from_parser(ast, p, AST_ELSE_CLAUSE);
            ast_set_in_parser(p, ast);
            return true;
        }
        else
        {
            ast_free(ast);
            p->cursor = tmp;
            return false;
        }
    }

    p->cursor = tmp;
    return false;
}

char *ast_rule_if_to_string(struct ast_node *ast)
{
    char *str = malloc(sizeof(char) * 512);
    sprintf(str, "AST_RULE_IF(%ld)", ast->nb_children);
    return str;
}

int ast_rule_if_exec(struct ast_node *ast)
{
    struct ast_node *first_compound_list = ast->children[0];
    int res_exec_first = first_compound_list->exec(first_compound_list);
    if (res_exec_first == 0)
    {
        struct ast_node *seconde_compound_list = ast->children[1];
        return seconde_compound_list->exec(seconde_compound_list);
    }
    else if (ast->nb_children == 3)
    {
        struct ast_node *third_child = ast->children[2];
        return third_child->exec(third_child);
    }
    return 0;
}

struct ast_node *ast_rule_if_init()
{
    struct ast_node *ast = ast_init(AST_RULE_IF, NULL);
    ast->to_string = ast_rule_if_to_string;
    ast->exec = ast_rule_if_exec;
    return ast;
}