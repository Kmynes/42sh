#include <parser/rules/rules.h>

bool read_case_clause_element(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (parser_readtext(p, ";;")
        && ZERO_OR_MANY(parser_readchar(p, '\n'))
        && read_case_item(p)
        )
        return true;

    p->cursor = tmp;
    return false;
}

bool read_case_clause(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_case_item(p))
    {
        // specific case when compound_list finished wih ';'
        if (p->input[p->cursor - 1] == ';' && p->input[p->cursor] == ';'
            && p->input[p->cursor + 1] != ';')
            p->cursor--;

        if (
            ZERO_OR_MANY(read_case_clause_element(p))
           && OPTIONAL(parser_readtext(p, ";;"))
           && ZERO_OR_MANY(parser_readchar(p, '\n')))
        {
            struct ast_node *ast = ast_case_clause_init();

            ast_recover_all_from_parser(ast, p, AST_CASE_ITEM);

            ast_set_in_parser(p, ast);

            return true;
        }

    }

    p->cursor = tmp;

    return false;
}

int read_case_clause_exec(struct ast_node *ast, char *word)
{
    if (ast->type != AST_CASE_CLAUSE)
        return 1;

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        struct ast_multiple_word *words = ast->data;

        for (size_t j = 0; j < words->nb_word; i++)
        {
            if (strcmp(word, words->words[i]) == 0)
                return child->exec(child);
        }
    }

    return 0; // by default ok
}

struct ast_node *ast_case_clause_init()
{
    struct ast_node *ast = ast_init(AST_CASE_CLAUSE, NULL);
    ast->exec_arg = read_case_clause_exec;
    return ast;
}