#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser/parser.h>

int execute_options(char *command, char *options);
char *option_translator(char *options, char *current_option);
unsigned first_empty(char *table);
void version_display(void);


int options_parser(char **argv, int argc)
// parses arguments directly from command line
{
    char *options = calloc(argc, 1);
    char *command = NULL;
    for (int i = 1; i < argc; i++)
    {
        options = option_translator(options, argv[i]);
        if (options[i-1] == 'c')
        {
            //printf("command1 = %s", argv[i+1]); REMOVE THIS - TESTING ONLY
            if (i+1 >= argc)
            {
                printf("Expected argument after -c option\n");
                return 1;
            }
            command = argv[i+1];
            i++;
        }
    }
    int error_code = execute_options(command, options);
    free(options);
    return error_code;
}

int execute_options(char *command, char *options)
{
    // printf("command is %s \n", command); REMOVE THIS - TESTING ONLY
    // printf("option table is %s \n", options); REMOVE THIS - TESTING ONLY

    int AST_print_flag = 0;
    int norc_flag = 0;
    printf("%s", command); // REMOVE THIS - testing dummy
    norc_flag++; // REMOVE THIS - testing dummy
    norc_flag--; // REMOVE THIS - testing dummy
    AST_print_flag++; // REMOVE THIS - testing dummy
    AST_print_flag--; // REMOVE THIS - testing dummy

    // do a first loop of options to get the flags (or fail if needed)
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
            case 'x':
                printf("Unknown option\n");
                return 1;
            case 'a':
                AST_print_flag = 1;
                break;
            case 'n':
                norc_flag = 1;
                break;
            default:
                break;
        }

    // do a second loop of the options to execute in the right order
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
        case 'v':
            version_display();
            return 0;
        case 'c':
            // insert call to run function here!!
            if (AST_print_flag)
                // insert call to AST_print function here!!
                AST_print_flag--; // REMOVE THIS - testing dummy
            return 0;
        default:
            break;
        }
    return 0;
}

char *option_translator(char *options, char *current_option)
// translates options into single character flags
{
    if (!strcmp(current_option, "--version"))
        options[first_empty(options)] = 'v';
    else if (!strcmp(current_option, "-c"))
        options[first_empty(options)] = 'c';
    else if (!strcmp(current_option, "--norc"))
        options[first_empty(options)] = 'n';
    else if (!strcmp(current_option, "--ast-print"))
        options[first_empty(options)] = 'a';
    else
        // default case throws an error
        options[0] = 'x';
    return options;
}

unsigned first_empty(char *table)
// returns the first empty index in an array
{
    unsigned first_free_index = 0;
    for (unsigned i = 0; table[i] != 0; i++)
        first_free_index++;
    return first_free_index;
}

void version_display()
// prints current version
{
    printf("Version 0.3\n");
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

