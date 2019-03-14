#pragma once

#include <parser/rules/rules.h>

void add_assignment_word(struct ast_assignment_word *list,
                         void *data);

size_t assignment_word_list_len(struct ast_assignment_word *list);
void assignment_word_list_free(struct ast_assignment_word *list);

