#include "parser/parser.h"
#include "options.h"

/**
** \file 42sh.c
** \brief This file contains the main file that is called when the executable
** is run.
** 
** It passes the argc and argv command line arguments to the
** options_parser.
** \author Blueshell42
** \version v0.3
** \date mars 2019
*/
int main(int argc, char **argv, char **env)
{
    options_parser(argv, argc, env);
    return 0;
}