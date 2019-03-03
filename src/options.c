#include "options.h"
#include <parser/parser.h>

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

    if (p->ast->type == AST_NODE_EMPTY)
    {}
    else if (p->ast->type ==  AST_NODE_INI_FILE)
    {}
    else if (p->ast->type ==  AST_NODE_SECTION)
    {}
    else if (p->ast->type ==  AST_NODE_KEY_VALUE)
    {}
    else if (p->ast->type ==  AST_NODE_ASSIGN)

    for (; (c = fgetc(fp)) != EOF ;)
        printf("%c",c);

    fclose(fp);

    return 0;
}
