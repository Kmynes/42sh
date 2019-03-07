#include "unit/parser/rules/test_rules.h"

//To reemploy
struct ast_assignment_word *gen_data_assignement_word(char *key, char *value)
{
    size_t size_struct_assingn = sizeof(struct ast_assignment_word);
    struct ast_assignment_word *data = malloc(size_struct_assingn);
    data->key = strdup(key);
    data->value = strdup(value);
    return data;
}

struct ast_redirection *gen_data_redirec(char *ionumber, char *redirect, char *word, 
    char *heredoc)
{
    struct ast_redirection *data = malloc(sizeof(struct ast_redirection));
    data->ionumber = ionumber ? strdup(ionumber): ionumber;
    data->redirect = redirect ? strdup(redirect): redirect;
    data->word = word ? strdup(word) : word;
    data->heredoc = heredoc ? strdup(heredoc) :heredoc;
    return data;
}

struct ast_node *gen_ast_redirect(struct ast_redirection *ast_r)
{
    struct ast_node *ast = ast_redirection_init(ast_r->ionumber, 
        ast_r->redirect, ast_r->word, ast_r->heredoc);

    return ast;
}

struct ast_node *gen_ast_assignement_word(struct ast_assignment_word *data)
{
    struct ast_node *ast = ast_assignment_word_init(data);
    return ast;
}

struct ast_node *gen_ast_prefix(enum ast_node_type type, void *data)
{
    struct ast_node *ast_child = NULL;
    if (type == AST_ASSIGNEMENT_WORD)
    {
        ast_child = gen_ast_assignement_word(data);
    }
    else if(type == AST_REDIRECTION)
    {
        ast_child = gen_ast_redirect(data);
        free(data);
    }

    struct ast_node *ast = ast_prefix_init();

    ast_set_in_parent(ast, ast_child);

    return ast;
}

static void test_read_simple_command1(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:\n\t- ");

    struct ast_node *ast = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("i", "0"));
    char *desc_ast = ast->to_string(ast);
    strcat(expected, desc_ast);
    test_rule(read_simple_command, "i=0", expected);
    ast_free(ast);
    free(desc_ast);
    free(expected);
}

static void test_read_simple_command2(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:\n\t- ");

    struct ast_node *ast = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("firstname", "toto"));
    char *desc_ast = ast->to_string(ast);
    strcat(expected, desc_ast);
    strcat(expected, "\n\t- ");
    ast_free(ast);
    free(desc_ast);

    struct ast_node *ast2 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("lastename", "SH"));
    char *desc_ast2 = ast2->to_string(ast2);
    strcat(expected, desc_ast2);
    strcat(expected, "\n\t- ");
    ast_free(ast2);
    free(desc_ast2);

    struct ast_node *ast3 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("date_of_birth", "01_01_2019"));
    char *desc_ast3 = ast3->to_string(ast3);
    strcat(expected, desc_ast3);
    ast_free(ast3);
    free(desc_ast3);

    test_rule(read_simple_command, "firstname=toto lastename=SH date_of_birth=01_01_2019", expected);
    free(expected);
}


static void test_read_simple_command2_5(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:\n\t- ");

    struct ast_node *ast = gen_ast_prefix(AST_REDIRECTION, 
        gen_data_redirec("2", ">", "42.sh", NULL));
    char *desc_ast = ast->to_string(ast);
    strcat(expected, desc_ast);
    strcat(expected, "\n\t- ");
    ast_free(ast);
    free(desc_ast);

    struct ast_node *ast2 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("lastename", "SH"));
    char *desc_ast2 = ast2->to_string(ast2);
    strcat(expected, desc_ast2);
    strcat(expected, "\n\t- ");
    ast_free(ast2);
    free(desc_ast2);

    struct ast_node *ast3 = gen_ast_prefix(AST_REDIRECTION, 
        gen_data_redirec("54", "<&", "file_name.sh", NULL));
    char *desc_ast3 = ast3->to_string(ast3);
    strcat(expected, desc_ast3);
    ast_free(ast3);
    free(desc_ast3);

    test_rule(read_simple_command, "2>42.sh lastename=SH 54<&file_name.sh", expected);
    free(expected);
}

void test_read_simple_command(void)
{
    //Simple commande with one prefix 
    test_read_simple_command1();

    //Simple commande with multiple prefix
    test_read_simple_command2();
    test_read_simple_command2_5();

    //Simple commande with zero prefix and 1 element

    //Simple commande with zero prefix and many element

    //Simple commande with many prefix and 1 element

    //Simple commande with many prefix and many element


}