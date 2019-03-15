#include "ast_print.h"
#include "./parser/parser.h"

int ast_print(struct ast_node *ast)
{
    if (ast == NULL)
        return 1;
/*
    FILE *fp = fopen("../ast.dot", "w");
    char *c;

    if (fp == NULL)
        return 1;

    fprintf()
    for (size_t i = 0; i < ast->nb_children; i++) //boucle permetant de parcourir le parseur et de récup tt les ast a print
    {
        //
    }

    fclose(fp);
*/
    return 0;
}
