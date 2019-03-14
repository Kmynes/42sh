#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser/parser.h>
#include <execution/execute_command.h>
#include <interactive/prompt.h>
#include "options.h"
/**
 * \file options.c
 * \brief option parser called by 42sh main function.
 * \author Blueshell42
 * \version 0.3
 * \date mars 2019
 *
 * Manages options sent by main and calls different parts of the code..
 *
 */
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
        if (options[i - 1] == 'c')
        {
            if (i + 1 >= argc)
            {
                printf("Expected argument after -c option\n");
                return 1;
            }
            command = argv[i + 1];
            i++;
        }
    }
    int error_code = execute_options(command, options);
    free(options);
    return error_code;
}

int execute_options(char *command, char *options)
{
    int AST_print_flag = 0;
    int norc_flag = 0;
    int res;
    norc_flag++; // REMOVE THIS - testing dummy
    norc_flag--; // REMOVE THIS - testing dummy

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

    // do a second loop of the options to execute in tder
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
            case 'v':
                version_display();
                return 0;
            case 'c':
                res = execute_command(command);
                // insert call to run function here!!
                if (AST_print_flag)
                    // insert call to AST_print function here!!
                    AST_print_flag--; // REMOVE THIS - testing dummy
                return res;
            default:
                break;
        }

    if (!(has_options(options, 'c') || has_options(options, 'v')))
        create_prompt();

    return 0;
}

bool has_options(char *options, char option)
{
    for (size_t i = 0; options[i]; i++)
        if (options[i] == option)
            return true;

    return false;
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
