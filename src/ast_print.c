#include <libgen.h>
#include "ast_print.h"

/**
** \file ast_print.c
** \brief Contains functions related to printing the AST
** \author Yann
** \version v0.3
** \date March 2019
*/

int table[29] = {0};

/**
** \brief This function removes any "(*)" pathern in strings
** \param input : the string from witch the patern will be removed from
*/
void remove_parenthesis(char *input)
{
    for (size_t i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '(')
        {
            size_t k = i;
            for (; input[k] != ')'; k++);

            k = k - i + 1;

            for (size_t z = i; input[z] != '\0'; z++)
                input[z] = input[z+k];
        }
    }
}

/**
** \brief This function removes the first four chars at the begening strings
** \param input : the string from witch the patern will be removed from
*/
void remove_start(char *input)
{
    for (size_t i = 0; input[i] != '\0'; i++)
        input[i] = input[i+4];
}

/**
** \brief This function increment one of the table's element concidering input
** \param input : the tested input
** \param table : the table that will be changed
** \param touch : 0 if the value shall not change and 1 if it shoul increase
*/
int increment_in_table(int *table, struct ast_node *input, int touch)
{
    if (input->type == AST_NODE_EMPTY)
    {
        if (touch == 1)
            table[0] = table[0]+1;
        return table[0]-1;
    }

    if (input->type == AST_NODE_INI_FILE)
    {
        if (touch == 1)
            table[1] = table[1]+1;
        return table[1]-1;
    }

    if (input->type == AST_NODE_SECTION)
    {
        if (touch == 1)
            table[2] = table[2]+1;
        return table[2]-1;
    }

    if  (input->type == AST_NODE_KEY_VALUE)
    {
        if (touch == 1)
            table[3] = table[3]+1;
        return table[3]-1;
    }

    if (input->type == AST_NODE_ASSIGN)
    {
        if (touch == 1)
            table[4] = table[4]+1;
        return table[4]-1;
    }

    if (input->type == AST_INPUT)
    {
        if (touch == 1)
            table[5] = table[5]+1;
        return table[5]-1;
    }

    if (input->type == AST_LIST)
    {
        if (touch == 1)
            table[6] = table[6]+1;
        return table[6]-1;
    }

    if (input->type == AST_AND_OR)
    {
        if (touch == 1)
            table[7] = table[7]+1;
        return table[7]-1;
    }

    if (input->type == AST_PIPELINE)
    {
        if (touch == 1)
            table[8] = table[8]+1;
        return table[8]-1;
    }

    if (input->type == AST_COMMAND)
    {
        if (touch == 1)
            table[9] = table[9]+1;
        return table[9]-1;
    }

    if (input->type == AST_SIMPLE_COMMAND)
    {
        if (touch == 1)
            table[10] = table[10]+1;
        return table[10]-1;
    }

    if (input->type == AST_SHELL_COMMAND)
    {
        if (touch == 1)
            table[11] = table[11]+1;
        return table[11]-1;
    }

    if (input->type == AST_FUNCDEC)
    {
        if (touch == 1)
            table[12] = table[12]+1;
        return table[12]-1;
    }

    if (input->type == AST_REDIRECTION)
    {
        if (touch == 1)
            table[13] = table[13]+1;
        return table[13]-1;
    }

    if (input->type == AST_PREFIX)
    {
        if (touch == 1)
            table[14] = table[14]+1;
        return table[14]-1;
    }

    if (input->type == AST_ELEMENT)
    {
        if (touch == 1)
            table[15] = table[15]+1;
        return table[15]-1;
    }

    if (input->type == AST_COMPOUND_LIST)
    {
        if (touch == 1)
            table[16] = table[16]+1;
        return table[16]-1;
    }

    if (input->type == AST_RULE_FOR)
    {
        if (touch == 1)
            table[17] = table[17]+1;
        return table[17]-1;
    }

    if (input->type == AST_RULE_WHILE)
    {
        if (touch == 1)
            table[18] = table[18]+1;
        return table[18]-1;
    }

    if (input->type == AST_RULE_UNTIL)
    {
        if (touch == 1)
            table[19] = table[19]+1;
        return table[19]-1;
    }

    if (input->type == AST_RULE_CASE)
    {
        if (touch == 1) 
            table[20] = table[20]+1;
        return table[20]-1;
    }

    if (input->type == AST_RULE_IF)
    {
        if (touch == 1)
            table[21] = table[21]+1;
        return table[21]-1;
    }

    if (input->type == AST_ELSE_CLAUSE)
    {
        if (touch == 1)
            table[22] = table[22]+1;
        return table[22]-1;
    }

    if (input->type == AST_DO_GROUP)
    {
        if (touch == 1)
            table[23] = table[23]+1;
        return table[23]-1;
    }

    if (input->type == AST_CASE_CLAUSE)
    {
        if (touch == 1)
        table[24] = table[24]+1;
        return table[24]-1;
    }

    if (input->type == AST_CASE_ITEM)
    {
        if (touch == 1)
            table[25] = table[25]+1;
        return table[25]-1;
    }

    if (input->type == AST_HEREDOC)
    {
        if (touch == 1)
            table[26] = table[26]+1;
        return table[26]-1;
    }

    if (input->type == AST_ASSIGNEMENT_WORD)
    {
        if (touch == 1)
            table[27] = table[27]+1;
        return table[27]-1;
    }

    if (input->type == AST_WORD)
    {
        if (touch == 1)
            table[28] = table[28]+1;
        return table[28]-1;
    }

    return -1;

}

/**
** \brief This function generates the DOT file
** \param ast: represents the ast that will be used to print into the dotfile
** \param stream: represents the file stream in which the data of the ast will
** be printed
*/
int ast_print(struct ast_node *ast, FILE *stream)
{
    if (ast == NULL)
        return 1;

    int first_one = 0;

    if (stream == NULL)
    {
        char path[1024];
        getcwd(path, sizeof(path));
        strcat(path, "~/doc/ast.dot");
        stream = fopen(path, "w");
        first_one = 1;
        ast = ast->children[0];

        if (stream == NULL)
            return 1;
    }

    if (first_one == 1)
        fprintf(stream, "digraph ast {\n");

    char *ast_string = ast->to_string(ast);
    remove_start(ast_string);
    remove_parenthesis(ast_string);
    int no_of_ast = 0;
    if (first_one == 0)
        no_of_ast = increment_in_table(table, ast, 0);
    else
        no_of_ast = increment_in_table(table, ast, 1);

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        char *ast_child_str = child->to_string(child);
        remove_start(ast_child_str);
        remove_parenthesis(ast_child_str);
        int no_of_child = increment_in_table(table, child, 1);

        fprintf(stream, "\t\"%s_%d\" -> \"%s_%d\";\n", ast_string, no_of_ast,
                ast_child_str, no_of_child);

        free(ast_child_str);
        ast_print(child, stream);
    }

    free(ast_string);
    if (first_one == 1)
    {
        fprintf(stream, "}");
        fclose(stream);
    }

    return 0;
}
