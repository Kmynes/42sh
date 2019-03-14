#include <errors.h>
#include "parser/parser.h"
#include "options.h"
/** \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */
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
