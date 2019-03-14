#include "ast_print.h"
#include "./parser/parser.h"
/**
 * \file ast_print.c
 * \brief Contains functions related to printing the AST
 * \author Yann
 * \version v0.3
 * \date March 2019
 */
int ast_print(struct ast_node *ast)
{
    /*
    FILE *fp = fopen("../ast.dot", "w");
    char *c;

    if (fp == NULL)
        return 1;

    while() //boucle permetant de parcourir le parseur et de récup tt les ast a print
    {
        case //ici faire un switch case
    }

    fclose(fp);
    */

    if (ast == NULL)
        return 1;

    return 0;
}
