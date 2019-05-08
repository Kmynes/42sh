#pragma once
#include <stdio.h>
#include <sys/stat.h>
#include <readline/history.h>
#include "../../parser/rules/rules.h"
#include "../../parser/parser.h"

bool read_builtin_history(char *input);

void put_in_history(char *input);

int my_read_history(char **voidarg);