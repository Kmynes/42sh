#include <parser/rules/rules.h>

bool read_list1(struct parser *p)
{
    unsigned int tmp = p->cursor;

    parser_begin_capture(p, "list_op");
    if ((parser_readchar(p, ';')
        || parser_readchar(p, '&'))
        && parser_end_capture(p, "list_op")
        && read_and_or(p))
    {
        return true;
    }

    parser_remove_capture_by_tag(p, "list_op");

    p->cursor =tmp;

    return false;
}

bool read_list(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (read_and_or(p))
    {
        struct ast_node *ast = ast_list_init();

        while (true)
        {
            struct ast_node *ast_and_or = ast_get_from_parser(p, AST_AND_OR);
            ast_set_in_parent(ast, ast_and_or);
            if (!read_list1(p))
                break;

            char *op = parser_get_capture(p, "list_op");
            struct ast_node *ast_op = ast_word_init(op);
            ast_set_in_parent(ast, ast_op);
        }

        if (parser_readchar(p, ';')
         || parser_readchar(p, '&'))
        {

        }

        ast_set_in_parser(p, ast);
        return true;
    }

    parser_remove_capture_by_tag(p, "list_op");

    p->cursor = tmp;

    return false;
}

int ast_list_exec(struct ast_node *ast)
{
    if (ast->type != AST_LIST)
        return 1;

    int res = ast->children[0]->exec(ast->children[0]);
    
    for (size_t i = 1; ast->nb_children > i; i += 2)
    {
        char *op = ast->children[i]->data;
        if (res  == 0 || strcmp(op, ";") == 0)
            res = ast->children[i + 1]->exec(ast->children[i + 1]);
        else
            return 1;
    }

    return res;
}

struct ast_node *ast_list_init()
{
    struct ast_node *ast = ast_init(AST_LIST, NULL);
    ast->exec = ast_list_exec;
    return ast;
}