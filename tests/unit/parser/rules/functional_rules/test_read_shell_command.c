#include "unit/parser/rules/test_rules.h"

static void test_read_shell_command_bracket(void)
{
    char *input = "{echo toto}";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_bracket (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_shell_command_bracket (2)");

    ast_free(ast);
}

static void test_read_shell_command_parens(void)
{
    char *input = "(echo toto)";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_parens (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_COMPOUND_LIST;
    print_state_test(check, "test_read_shell_command_parens (2)");

    ast_free(ast);
}

static void test_read_shell_command_for(void)
{
    char *input = "for var do\n\ntcheck=true;\ndone";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_for (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_RULE_FOR;
    print_state_test(check, "test_read_shell_command_for (2)");
    ast_free(ast);
}

static void test_read_shell_command_while(void)
{
    char *input = "while\n\necho hello\ndo\nls\ndone";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_while (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_RULE_WHILE;
    print_state_test(check, "test_read_shell_command_while (2)");
    ast_free(ast);
}

static void test_read_shell_command_until(void)
{
    char *input = "until\n\necho hello\ndo\nls\ndone";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_until (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_RULE_UNTIL;
    print_state_test(check, "test_read_shell_command_until (2)");
 
    ast_free(ast);
}

static void test_read_shell_command_case(void)
{
    char *input = "case var in\ncase1)\nstart\n;;esac";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_case (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_RULE_CASE;
    print_state_test(check, "test_read_shell_command_case (2)");

    ast_free(ast);
}

static void test_read_shell_command_if(void)
{
    char *input = "if\n\n!shool=Epita;\n\n\nthen\n\necho ok\n\n\nfi";
    bool check = test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)");
    print_state_test(check, "test_read_shell_command_if (1)");

    struct ast_node *ast = ast_from_read(read_shell_command, input);
    check = ast->children[0]->type == AST_RULE_IF;
    print_state_test(check, "test_read_shell_command_if (2)");

    ast_free(ast);
}

void test_read_shell_command_fail(void)
{
    // protected_word
    bool check = test_not_rule(read_shell_command, "for");
    print_state_test(check, "test_read_shell_command_fail");
}

void test_read_shell_command(void)
{
    test_read_shell_command_bracket();
    test_read_shell_command_parens();
    test_read_shell_command_for();
    test_read_shell_command_while();
    test_read_shell_command_until();
    test_read_shell_command_case();
    test_read_shell_command_if();
    test_read_shell_command_fail();
}