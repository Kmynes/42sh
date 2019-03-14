#include "ast_print.h"
#include "./parser/parser.h"

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
