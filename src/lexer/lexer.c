#include "lexer.h"
#include <stdlib.h>

struct lexer *lexer_init(void)
{
    return malloc(sizeof(struct lexer));
}
