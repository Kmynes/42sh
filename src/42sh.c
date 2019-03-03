#include "parser/parser.h"
#include "execution/execute_ast.h"
#include "options.h"

int main(int argc, char ** argv)
{
    options_parser(argv, argc);
    return 0;
}