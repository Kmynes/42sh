#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int options_parser(char **argv, int argc, char **env);
bool has_options(char *options, char option);
int exec_file(char *file_name, bool ast_print_flag);