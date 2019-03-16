#include "assignment_word.h"

void add_assignment_word(struct ast_assignment_word *list,
                         void *data)
{
    while (list->next != NULL)
        list = list->next;
    list->next = data;
}

size_t assignment_word_list_len(struct ast_assignment_word *list)
{
    if (list == NULL)
        return 0;
    size_t i = 0;

    while (list->next != NULL)
    {
        list = list->next;
        i++;
    }

    return ++i;
}