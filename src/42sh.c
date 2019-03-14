#include <errors.h>
#include "parser/parser.h"
#include "options.h"
/**
 * \file 42sh.c
 * \brief Programme
 * \author Blueshell42
 * \version 0.3
 * \date mars 2019
 *
 * Programme de test pour l'objet de gestion des chaînes de caractères Str_t.
 *
 */
int main(int argc, char ** argv)
{
    options_parser(argv, argc);
    return 0;
}
