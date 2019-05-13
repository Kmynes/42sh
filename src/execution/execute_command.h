#pragma once

#include <stdbool.h>

int execute_command(char *command, int ast_print_flag, bool prompt_mode);
int execute_shell_no_option(int ast_print_flag);