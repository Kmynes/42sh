#include "unit/parser/rules/test_rules.h"

char *get_else_clause(void)
{
    char *else_clause = malloc(sizeof(char) * 512);

    char *input = "elif\n\n!shool=Epita;\n\n\nthen\n\n!i=0;\n\n\n";
    char *input2 = "elif\n\n!shool=Epitech;\n\n\nthen\n\ndocker=compose;\n";
    char *input3 = "else\n\n!shool=42;\n\n\n";

    sprintf(else_clause, "%s%s%s", input, input2, input3);

    return else_clause;
}

void test_read_rule_if1(void)
{
    char *input = "if\n\n!shool=Epita;\n\n\nthen\n\n!shool=Epita;\n\n\nfi";
    test_rule(read_rule_if, input, "AST_RULE_IF(2)");
}

void test_read_rule_if2(void)
{
    char *part1 = "if\n\n!shool=Epita;\n\n\nthen\n\n!shool=Epita;\n\n\n";
    char *else_clause = get_else_clause();
    char input[strlen(part1) + strlen(else_clause)];

    sprintf(input, "%s%sfi", part1, else_clause);
    test_rule(read_rule_if, input, "AST_RULE_IF(3)");
    free(else_clause);
}

/*
static void test_rule_if_global_exec(void)
{
    char *input = calloc(sizeof(char), 512);
    strcat(input, "path='tests/sh_test_files'\n");
    strcat(input, "empty_file=\"${path}/empty_file\"\n");
    strcat(input, "printer=\"${path_file}/printer.py\"\n");
    strcat(input, "if cat $empty_file then\n\n");
    strcat(input, "    python3 $printer \"file ${path_file} printed!\"\n");
    strcat(input, "fi");
    struct parser *p = parser_new_from_string(input);

    do
    {
        read_input(p);
    }
    while (p->input[p->cursor]);

    struct ast_node *ast = NULL;
    for (size_t i = 0; i < p->ast->nb_children; i++)
    {
        ast = p->ast->children[i];
        ast->exec(ast);
    }

    free(input);
    parser_free(p);
}*/

void test_read_rule_if(void)
{
    test_read_rule_if1();
    test_read_rule_if2();
    //test_rule_if_global_exec();
}