#pragma once

#include <stddef.h>
#include <stdbool.h>


int options_parser(char **argv, int argc);
bool has_options(char *options, char option);
