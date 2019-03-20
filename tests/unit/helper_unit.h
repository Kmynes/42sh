#include <utils/function_utils.h>
#include <parser/rules/rules.h>

extern bool global_condition;

void execute_sh_test_files(const char *path);
void print_state_test(bool condition, char *func_name);