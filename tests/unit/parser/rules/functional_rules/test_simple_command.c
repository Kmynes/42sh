#include "unit/parser/rules/test_rules.h"


static void add_to_string_as_child(char *expected, struct ast_node *ast_child)
{
    char *desc_ast = ast_child->to_string(ast_child);
    strcat(expected, "\n\t- ");
    strcat(expected, desc_ast);
    free(desc_ast);
    ast_free(ast_child);
}

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
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("i", "0"));

    add_to_string_as_child(expected, ast);

    test_rule(read_simple_command, "i=0", expected);
    free(expected);
}

static void test_read_simple_command2(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("firstname", "toto"));
    add_to_string_as_child(expected, ast);

    struct ast_node *ast2 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("lastename", "SH"));
    add_to_string_as_child(expected, ast2);

    struct ast_node *ast3 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("date_of_birth", "01_01_2019"));
    add_to_string_as_child(expected, ast3);

    test_rule(read_simple_command, "firstname=toto lastename=SH date_of_birth=01_01_2019", expected);
    free(expected);
}


static void test_read_simple_command2_5(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast = gen_ast_prefix(AST_REDIRECTION, 
        gen_data_redirec("2", ">", "42.sh", NULL));

    add_to_string_as_child(expected, ast);

    struct ast_node *ast2 = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
        gen_data_assignement_word("lastename", "SH"));
    add_to_string_as_child(expected, ast2);

    struct ast_node *ast3 = gen_ast_prefix(AST_REDIRECTION, 
        gen_data_redirec("54", "<", "file_name.sh", NULL));
    add_to_string_as_child(expected, ast3);

    test_rule(read_simple_command, "2>42.sh lastename=SH 54<file_name.sh", expected);
    free(expected);
}

static void test_read_simple_command3(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast_element = gen_ast_element(
        gen_data_ast_element(strdup("The_real_test")));
    add_to_string_as_child(expected, ast_element);

    test_rule(read_simple_command, "The_real_test", expected);

    free(expected);
}

static void test_read_simple_command4(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast_element = gen_ast_element(
        gen_data_ast_element(strdup("epitech")));
    add_to_string_as_child(expected, ast_element);

    struct ast_node *ast_redirect = ast_redirection_init(strdup("4242"), 
    strdup(">>"), strdup("some_test.sh"), NULL);

    struct ast_node *ast_element2 = gen_ast_element(NULL);
    ast_set_in_parent(ast_element2, ast_redirect);
    add_to_string_as_child(expected, ast_element2);

    struct ast_node *ast_element3 = gen_ast_element(
        gen_data_ast_element(strdup("epi_tatech")));
    add_to_string_as_child(expected, ast_element3);

    test_rule(read_simple_command, "epitech 4242>>some_test.sh epi_tatech", expected);

    free(expected);
}

static void test_read_simple_command5(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");
    
    struct ast_node *ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("school", "epita"));
    add_to_string_as_child(expected, ast_prefix);

    ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("foo", "bar"));
    add_to_string_as_child(expected, ast_prefix);

    ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("school2", "epitech"));
    add_to_string_as_child(expected, ast_prefix);

    struct ast_node *ast_element = gen_ast_element(
        gen_data_ast_element(strdup("SOME_WORD")));
    add_to_string_as_child(expected, ast_element);

    char *input = "school=epita foo=bar school2=epitech SOME_WORD";
    test_rule(read_simple_command, input, expected);
    free(expected);
}

static void test_read_simple_command6(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("docker", "compose"));
    add_to_string_as_child(expected, ast_prefix);

    struct ast_node *ast_element = gen_ast_element(
        gen_data_ast_element(strdup("epitech")));
    add_to_string_as_child(expected, ast_element);

    struct ast_node *ast_redirect = ast_redirection_init(strdup("356"), 
    strdup(">>"), strdup("file_to_edit.sh"), NULL);
    struct ast_node *ast_element2 = gen_ast_element(NULL);
    ast_set_in_parent(ast_element2, ast_redirect);
    add_to_string_as_child(expected, ast_element2);

    struct ast_node *ast_element3 = gen_ast_element(
        gen_data_ast_element(strdup("epita")));
    add_to_string_as_child(expected, ast_element3);

    test_rule(read_simple_command, "docker=compose epitech 356>>file_to_edit.sh epita", expected);
    free(expected);
}

static void test_read_simple_command7(void)
{
    char *expected = malloc(sizeof(char) * 1024);
    strcpy(expected, "simple_command:");

    struct ast_node *ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("school", "epita"));
    add_to_string_as_child(expected, ast_prefix);

    ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("foo", "bar"));
    add_to_string_as_child(expected, ast_prefix);

    ast_prefix = gen_ast_prefix(AST_ASSIGNEMENT_WORD, 
    gen_data_assignement_word("school2", "epitech"));
    add_to_string_as_child(expected, ast_prefix);

    struct ast_node *ast_element = gen_ast_element(
        gen_data_ast_element(strdup("SOME_WORD_2")));
    add_to_string_as_child(expected, ast_element);

    struct ast_node *ast_redirect = ast_redirection_init(strdup("4566"), 
    strdup(">&"), strdup("/dev/null"), NULL);
    ast_element = gen_ast_element(NULL);
    ast_set_in_parent(ast_element, ast_redirect);
    add_to_string_as_child(expected, ast_element);


    ast_redirect = ast_redirection_init(strdup("0"), 
    strdup("<&"), strdup(".bashrc"), NULL);
    ast_element = gen_ast_element(NULL);
    ast_set_in_parent(ast_element, ast_redirect);
    add_to_string_as_child(expected, ast_element);

    char *input = "school=epita foo=bar school2=epitech SOME_WORD_2 4566>&/dev/null 0<&.bashrc";
    test_rule(read_simple_command, input, expected);

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

}