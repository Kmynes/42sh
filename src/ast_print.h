#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "./parser/parser.h"

int ast_print(struct ast_node *ast, FILE *stream);