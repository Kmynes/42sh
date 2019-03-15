#pragma once
#include <stdbool.h>

int options_parser(char **argv, int argc, char **env);
bool has_options(char *options, char option);