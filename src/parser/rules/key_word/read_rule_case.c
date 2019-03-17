#include <parser/rules/rules.h>
/**
 * \file read_rule_case.c
 * \brief reads rule_case grammar as specified by the subject.
 *
 * rule_case: 'case' WORD ('\n')* 'in' ('\n')* [case_clause] 'esac'
 * \author Yann
 * \version 0.3
 * \date March 2019
 */
bool read_rule_case(struct parser *p)
{
    unsigned int tmp = p->cursor;
    struct ast_multiple_word *data = multiple_word_init();

    if (parser_readtext(p, "case")
        && read_spaces(p)
        && parser_begin_capture(p, "rule_case_0")
        && read_word(p)
        && parser_end_capture(p, "rule_case_0")
        && read_spaces(p)
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && parser_readtext(p, "in")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && OPTIONAL(read_case_clause(p))
        && parser_readtext(p, "esac"))
    {
        data->nb_word += 1;
        data->words[0] = parser_get_capture(p, "rule_case_0");
        struct ast_node *ast = ast_rule_case_init(data);
        ast_recover_all_from_parser(ast, p, AST_CASE_CLAUSE);
        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;
    multiple_word_free(data);

    return false;
}

void ast_rule_case_free(void *data)
{
    multiple_word_free(data);
}

struct ast_node *ast_rule_case_init(void *data)
{
    struct ast_node *ast = ast_init(AST_RULE_CASE, data);
    ast->free = ast_rule_case_free;
    return ast;
}