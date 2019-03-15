#include "ast_print.h"
#include "./parser/parser.h"
/**
 * \file ast_print.c
 * \brief Contains functions related to printing the AST
 * \author Yann
 * \version v0.3
 * \date March 2019
 */

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
        FILE *stream = fopen("../ast.dot", "w");
        first_one = 1;

        if (stream == NULL)
            return 1;
    }

    if (first_one == 1)
        fprintf(stream, "digraph ast {\n");

    char *ast_string = ast->to_string(ast);

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
	char *ast_child_str = child->to_string(child);
        fprintf(stream, "\t%s -> %s;\n", ast_string, ast_child_str);
	ast_print(child, stream);
    }

    if (first_one == 1)
    {
        fprintf(stream, "}");
        fclose(stream);
    }

    return 0;
}

/**
 * \brief This function read the DOT file and print it on the output
 * \
 * \
 * \
 */
