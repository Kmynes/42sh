#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_options(char * command, char * options);
char* option_translator(char * options, char * current_option);
unsigned first_empty(char * table);
void version_display();



int options_parser(char ** argv, int argc)
// parses arguments directly from command line
{
    char * options = malloc(argc);
    char * command = malloc(100);
    for (int i = 1; i < argc; i++)
    {
        options = option_translator(options, argv[i]);
        if (options[i-1] == 'c')
        {
            //printf("command1 = %s", argv[i+1]); REMOVE THIS - TESTING ONLY
            command = argv[i+1];
            i++;
        }
    }
    int error_code = execute_options(command, options);
    return error_code;
}

int execute_options(char * command, char * options)
{
    //this is where you will place the run function call
    // printf("command is %s \n", command); REMOVE THIS - TESTING ONLY
    // printf("option table is %s \n", options); REMOVE THIS - TESTING ONLY

    int AST_print_flag = 0;
    int norc_flag = 0;
    int run_flag = 0;
    command[0] = command[0] + 1 - 1; // REMOVE THIS - testing dummy
    norc_flag++; // REMOVE THIS - testing dummy
    norc_flag--; // REMOVE THIS - testing dummy
    AST_print_flag++; // REMOVE THIS - testing dummy
    AST_print_flag--; // REMOVE THIS - testing dummy
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
            case 'v':
                version_display();
                return 0;
            case 'x':
                printf("Unknown option");
                return 1;
            case 'a':
                AST_print_flag = 1;
                break;
            case 'n':
                norc_flag = 1;
                break;
            case 'c':
                run_flag = 1;
            default:
                break;
        }
    if (run_flag)
        // insert call to run function here with other flags
        AST_print_flag++; // REMOVE THIS - testing dummy

    return 0;
}

char* option_translator(char * options, char * current_option)
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

unsigned first_empty(char * table)
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
int ast_print()
{
    FILE *fp = fopen("../ast.dot", "r");
    char c;

    if (fp == NULL)
        return 1;

    for (; (c = fgetc(fp)) != EOF ;)
        printf("%c",c);

    fclose(fp);

    return 0;
}

