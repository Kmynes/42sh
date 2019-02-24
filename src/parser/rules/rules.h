#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool parser_readalpha(struct parser *p);

bool parser_readnum(struct parser *p);

bool parser_readletter(struct parser *p);

bool parser_readalphanum(struct parser *p);

bool parser_readeol(struct parser *p);

bool parser_readidentifier(struct parser *p);

bool parser_readinteger(struct parser *p);