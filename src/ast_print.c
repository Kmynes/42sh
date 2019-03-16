#include <libgen.h>
#include "test_ast_print.h"
#include "./parser/parser.h"

/**
 * \file ast_print.c
 * \brief Contains functions related to printing the AST
 * \author Yann
 * \version v0.3
 * \date March 2019
 */

/**
 * \brief This function remouves any "(*)" pathern in strings
 * \param input : the string from witch the patern will be remouved from
 */
void remouve_parenthesis(char *input)
{
    for (size_t i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '(')
        {
            size_t k = i;
            for (; input[k] != ')'; k++)

            k = i - k + 1;

            for (size_t z = i; input[z] != '\0'; z++)
                input[z] = input[z+k];
        }
    }
}

/**
 * \brief This function generates the DOT file
 * \param ast : this represent the ast that will be used to print into the dotfile
 * \param stream : represents the file stream in witch the datas of the ast will be printed
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
        strcat(path, "/doc/ast.dot");
        stream = fopen(path, "w");
        first_one = 1;

        if (stream == NULL)
            return 1;
    }

    if (first_one == 1)
        fprintf(stream, "digraph ast {\n");

    char *ast_string = ast->to_string(ast);
    remouve_parenthesis(ast_string);

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        char *ast_child_str = child->to_string(child);
        remouve_parenthesis(ast_child_str);

        int node_number_plus = node_number + 1;
        fprintf(stream, "\t%s%d -> %s%d;\n", ast_string, node_number, ast_child_str, node_number_plus);
        node_number += 2;
	    ast_print(child, stream);
    }

    if (first_one == 1)
    {
        fprintf(stream, "}");
        fclose(stream);
    }

    return 0;
}