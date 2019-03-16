#include "unit/parser/rules/test_rules.h"


static void test_read_compound_list_simple_and_or(void)
{
    char *input ="some_boolean";
    assert(test_rule(read_compound_list, input, "AST_COMPOUND_LIST(1)"));
    struct ast_node *ast = ast_from_read(read_compound_list, input);
    assert(ast->nb_children == 1);
    assert(ast->children[0]->type == AST_AND_OR);
    ast_free(ast);
}


static void test_read_compound_list_medium(void)
{
    char *input = malloc(sizeof(char) * 512);
    strcpy(input, "\n\nsome_boolean&&\n\nan_other_boolean");
    strcat(input, " ;\n\n");
    strcat(input, " easy_boolean&&\n\nan_other_easy_boolean");

    assert(test_rule(read_compound_list, input, "AST_COMPOUND_LIST(2)"));
    struct ast_node *ast = ast_from_read(read_compound_list, input);
    assert(ast->nb_children == 2);
    assert(ast->children[0]->type == AST_AND_OR);
    assert(ast->children[1]->type == AST_AND_OR);
    ast_free(ast);
    free(input);
}

static void test_read_compound_list_high(void)
{
    char *input = malloc(sizeof(char) * 512);
    strcpy(input, "\n\nsome_boolean&&\nsome_test_bool");
    strcat(input, " ;\n\n");
    strcat(input, " next_boolean&&\n\nboolean");
    strcat(input, " & \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    assert(test_rule(read_compound_list, input, "AST_COMPOUND_LIST(2)"));
    struct ast_node *ast = ast_from_read(read_compound_list, input);
    assert(ast->nb_children == 2);
    assert(ast->children[0]->type == AST_AND_OR);
    assert(ast->children[1]->type == AST_AND_OR);
    ast_free(ast);
    free(input);
}

void test_read_compound_list(void)
{
    test_read_compound_list_simple_and_or();
    test_read_compound_list_medium();
    test_read_compound_list_high();
}