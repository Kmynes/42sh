#include "options.h"
#include <stdio.h>
#include <stdlib.h>

// parse options as in myfind
struct list_options *get_options(char **argv, int argc)
{
    argv++;  // dummy
    argc--;  // dummy
    argc++;  // dummy
    argc--;  // dummy
    struct list_options *options = malloc(sizeof(struct list_options));
    options->len = 0;
    options->options = malloc(MAX_OPTIONS * (sizeof(struct option)));

    return options;
}

// ast print le fichier DOT ouvert est \"ast.dot\"
int ast_print(struct parser *p)
{
    FILE *fp = fopen("../ast.dot", "w");
    char c;

    if (fp == NULL)
        return 1;

    switch (p->ast)
    {
        case 'AST_NODE_EMPTY' :
            break;

        case 'AST_NODE_INI_FILE' :
            break;

        case 'AST_NODE_SECTION' :
           break;

        case 'AST_NODE_KEY_VALUE' :
            break;

        case 'AST_NODE_ASSIGN' :
            break;

    }
    for (; (c = fgetc(fp)) != EOF ;)
        printf("%c",c);

    fclose(fp);

    return 0;
}
