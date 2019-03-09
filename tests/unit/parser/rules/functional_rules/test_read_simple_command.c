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

struct ast_node *gen_ast_element(void *data)
{
    return ast_element_init(data);
}

struct ast_element *gen_data_ast_element(char * elt)
{
    struct ast_element *ast_elt = malloc(sizeof(struct ast_element));
    ast_elt->elt = elt;
    return ast_elt;
}

static void test_read_simple_command1(void)
{
    assert(test_rule(read_simple_command, "i=0", "AST_SIMPLE_COMMAND(1)"));
}

static void test_read_simple_command2(void)
{
    assert(test_rule(read_simple_command, "firstname=toto lastename=SH date_of_birth=01_01_2019", "AST_SIMPLE_COMMAND(3)"));
}


static void test_read_simple_command2_5(void)
{
    assert(test_rule(read_simple_command, "2>42.sh lastename=SH 54<file_name.sh", "AST_SIMPLE_COMMAND(3)"));
}

static void test_read_simple_command3(void)
{
    assert(test_rule(read_simple_command, "The_real_test", "AST_SIMPLE_COMMAND(1)"));
}

static void test_read_simple_command4(void)
{
    assert(test_rule(read_simple_command, "epitech 4242>>some_test.sh epi_tatech", "AST_SIMPLE_COMMAND(3)"));
}

static void test_read_simple_command5(void)
{
    char *input = "school=epita foo=bar school2=epitech SOME_WORD";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(4)"));
}

static void test_read_simple_command6(void)
{
    assert(test_rule(read_simple_command, "docker=compose epitech 356>>file_to_edit.sh epita", "AST_SIMPLE_COMMAND(4)"));
}

static void test_read_simple_command7(void)
{
    char *input = "school=epita foo=bar school2=epitech SOME_WORD_2 4566>&/dev/null 0<&.bashrc";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(6)"));
}

void test_read_simple_command8(void)
{
    assert(test_rule(read_simple_command, "toto", "AST_SIMPLE_COMMAND(1)"));
}

void test_read_simple_command(void)
{
    //Simple commande with one prefix 
    test_read_simple_command1();

    //Simple commande with multiple prefix
    test_read_simple_command2();
    test_read_simple_command2_5();

    //Simple commande with zero prefix and 1 element
    test_read_simple_command3();//Warning assume the [element] is a word

    //Simple commande with zero prefix and many element
    test_read_simple_command4();//Warning assume the first element is a word
    //else theire no distinction possible with prefix

    //Simple commande with many prefix and 1 element
    test_read_simple_command5();

    //Simple commande with one prefix and many element
    test_read_simple_command6();

    //Simple commande with many prefix and many element
    test_read_simple_command7();//Warning assume the first element is a word
    //else theire no distinction possible with prefix

    // just one command
    test_read_simple_command8();
}