#include "unit/parser/rules/test_rules.h"

static void test_read_shell_command_bracket(void)
{
    char *input = "{echo toto}";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    ast_free(ast);
}

static void test_read_shell_command_parens(void)
{
    char *input = "(echo toto)";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_COMPOUND_LIST);
    ast_free(ast);
}

static void test_read_shell_command_for(void)
{
    char *input = "for var do\n\ntcheck=true;\ndone";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_RULE_FOR);
    ast_free(ast);
}

static void test_read_shell_command_while(void)
{
    char *input = "while\n\necho hello\ndo\nls\ndone";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_RULE_WHILE);
    ast_free(ast);
}

static void test_read_shell_command_until(void)
{
    char *input = "until\n\necho hello\ndo\nls\ndone";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_RULE_UNTIL);
    ast_free(ast);
}

static void test_read_shell_command_case(void)
{
    char *input = "case var in\ncase1)\nstart\n;;esac";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_RULE_CASE);
    ast_free(ast);
}

static void test_read_shell_command_if(void)
{
    char *input = "if\n\n!shool=Epita;\n\n\nthen\n\necho ok\n\n\nfi";
    assert(test_rule(read_shell_command, input, "AST_SHELL_COMMAND(1)"));
    struct ast_node *ast = ast_from_read(read_shell_command, input);
    assert(ast->children[0]->type == AST_RULE_IF);
    ast_free(ast);
}

void test_read_shell_command_fail(void)
{
    // protected_word
    assert(test_not_rule(read_shell_command, "for"));
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