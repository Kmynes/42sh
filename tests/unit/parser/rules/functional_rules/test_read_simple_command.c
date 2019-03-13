#include "unit/parser/rules/test_rules.h"

static void test_read_simple_command1(void)
{
    assert(test_rule(read_simple_command, "i=0", "AST_SIMPLE_COMMAND(1)"));
}

static void test_read_simple_command2(void)
{
    char *input="firstname=toto lastename=SH date_of_birth=01_01_2019";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(3)"));
}


static void test_read_simple_command2_5(void)
{
    assert(test_rule(read_simple_command,
        "2>42.sh lastename=SH 54<file_name.sh", "AST_SIMPLE_COMMAND(3)"));
}

static void test_read_simple_command3(void)
{
    assert(test_rule(read_simple_command, "The_real_test", 
        "AST_SIMPLE_COMMAND(1)"));
}

static void test_read_simple_command4(void)
{
    char *input="epitech 4242>>some_test.sh epi_tatech";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(3)"));
}

static void test_read_simple_command5(void)
{
    char *input = "school=epita foo=bar school2=epitech SOME_WORD";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(4)"));
}

static void test_read_simple_command6(void)
{
    char *input="docker=compose epitech 356>>file_to_edit.sh epita";
    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(4)"));
}

static void test_read_simple_command7(void)
{
    char *input = malloc(sizeof(char) * 512);
    strcpy(input, "school=epita foo=bar school2=epitech");
    strcat(input, " SOME_WORD_2 4566>&/dev/null 0<&.bashrc");

    assert(test_rule(read_simple_command, input, "AST_SIMPLE_COMMAND(6)"));
    free(input);
}

void test_read_simple_command8(void)
{
    assert(test_rule(read_simple_command, "toto", "AST_SIMPLE_COMMAND(1)"));
}

void test_read_simple_command9(void)
{
    assert(test_rule(read_simple_command, "echo toto", "AST_SIMPLE_COMMAND(2)"));
}

void test_read_simple_command_fail(void)
{
    // protected_word
    assert(test_not_rule(read_simple_command, "for"));
}

void test_simple_command_exec(void)
{
    char *input= "i=0 j=23 find";
    struct parser *p = parser_new_from_string(input);
    read_simple_command(p);
    struct ast_node *ast_simple_cmd = p->ast->children[0];
    char *s = ast_simple_cmd->to_string(ast_simple_cmd);
    assert(strcmp(s, "AST_SIMPLE_COMMAND(3)") == 0);
//    ast_simple_cmd->exec(ast_simple_cmd);
    parser_free(p);
    free(s);
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
    test_read_simple_command9();

    test_read_simple_command_fail();

    //Test exec command
    test_simple_command_exec();
}