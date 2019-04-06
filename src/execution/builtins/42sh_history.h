#pragma once
#include <sys/stat.h>
#include "../../parser/rules/rules.h"
#include "../../parser/parser.h"

void put_in_history_file(char *input);

bool read_builtin_history(char *input);

void read_history();

void erease_tmp_history();