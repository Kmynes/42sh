#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser/parser.h>
#include <execution/execute_command.h>
#include <interactive/prompt.h>
#include <utils/option_util.h>
#include "options.h"
/**
** \file options.c
** \brief option parser called by 42sh main function.
** Manages arguments sent by main and calls different parts of the code..
** \author Daniel
** \version 0.3
** \date February 2019
*/
int execute_options(char *command, char *options);
char *option_translator(char *options, char *current_option);
unsigned first_empty(char *table);
void version_display(void);

/**
** \brief Add all envrionment variables to list of global key_value
** \param env is a list of all environment variable
*/
static void add_env_variables(char **env)
{
    char *key = NULL;
    char *value = NULL;
    while (*env)
    {
        char *var_env = *env;

        size_t len_name = 0;
        while (var_env[len_name] != '=')
            len_name++;

        key = calloc(sizeof(char), len_name + 1);
        strncpy(key, *env, len_name);

        char *val_env = var_env + len_name + 1;
        size_t len_val_env = strlen(val_env);
        value = calloc(sizeof(char), len_val_env + 1);
        strncpy(value, val_env, len_val_env);

        variables_add(key, value);
        free(key);
        free(value);
        env++;
    }
}

/**
** \brief Main function that is called and parses arguments directly from
** command line.
** \param argv a list of strings given as argument to 42sh
** \param argc an integer representing the number of arguments
** \param env a list of strings rep. environment variables
** \return error code. 1 for error, 0 for success.
*/
int options_parser(char **argv, int argc, char **env)
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
                printf("Expected argument after -c/-f option\n");
                return 1;
            }
            command = argv[i + 1];
            i++;
        }
        if (options[i - 1] == 'f')
        {
            command = argv[i];
            i++;
        }
    }

    add_env_variables(env);

    int error_code = execute_options(command, options);
    free(options);
    return error_code;
}

/**
** \brief executes options
** Does two loops. one to
** \param command a string representing the command given as argument to 42sh.
** \param options a string representing the options given as argument to 42sh.
** \return error code. 1 for error, 0 for success.
*/
int execute_options(char *command, char *options)
{
    int ast_print_flag = false;
    int norc_flag = false;
    int res;
    norc_flag++; // REMOVE THIS - testing dummy
    norc_flag--; // REMOVE THIS - testing dummy

    // do a first loop of options to get the flags (or fail if needed)
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
        case 'a':
            ast_print_flag = true;
            break;
        case 'n':
            norc_flag = true;
            break;
        default:
            break;
        }

    // do a second loop of the options to execute in tder
    for (unsigned i = 0; options[i]; i++)
        switch (options[i])
        {
        case 'f':
            if (fopen(command, "r") == NULL)
            {
                printf("42sh: %s: No such file or directory\n", command);
                return 1;
            }

            res = exec_file(command, ast_print_flag);
            return res;
        case 'v':
            version_display();
            return 0;
        case 'c':
            res = execute_command(command, ast_print_flag);
            return res;
        default:
            break;
        }

    if (!(has_options(options, 'c') || has_options(options, 'v')))
        return execute_shell_no_option(ast_print_flag);

    return 0;
}

bool has_options(char *options, char option)
{
    for (size_t i = 0; options[i]; i++)
        if (options[i] == option)
            return true;

    return false;
}

/**
** \brief translates options given as argument to be in string format.
** \param current_option a string representing the current otion to translate.
** \param options a string representing the options given as argument to 42sh.
** \return string options
*/
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
        // default case treats argument as filename
        options[first_empty(options)] = 'f';
    return options;
}

/**
** \brief Calculates first available index in a table
** \param table a string
** \return unsigned integer representing the first empty index
*/
unsigned first_empty(char *table)
// returns the first empty index in an array
{
    unsigned first_free_index = 0;
    for (unsigned i = 0; table[i] != 0; i++)
        first_free_index++;
    return first_free_index;
}

/**
** \brief Prints out current version number
*/
void version_display(void)
// prints current version
{
    printf("Version 0.3\n");
}