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
            for (; input[k] != ')'; k++)
                ;
            k = k - i + 1;

            for (size_t z = i; input[z] != '\0'; z++)
                input[z] = input[z + k];
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
        input[i] = input[i + 4];
}

/**
** \brief This function increment one of the table's element concidering input
** \param input : the tested input
** \param table : the table that will be changed
** \param touch : 0 if the value shall not change and 1 if it shoul increase
*/
int increment_in_table(int *table, struct ast_node *input, int touch)
{
    if (touch == 1)
        table[input->type] = table[input->type] + 1;

    return table[input->type] - 1;
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

        strcat(path, "/ast.dot");

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