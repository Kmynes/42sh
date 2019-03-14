#include <errors.h>
#include "parser/parser.h"
#include "options.h"
/**
 * \file 42sh.c
 * \brief This file contains the main file that is called when the executable is run.
 * \author Blueshell42
 * \version v0.3
 * \date mars 2019
 */
int main(int argc, char ** argv)
{
    options_parser(argv, argc);
    return 0;
}
