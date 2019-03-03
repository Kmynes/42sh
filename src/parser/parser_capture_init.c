#include "parser.h"

void free_list_capt_s(struct list_capt_s *capture)
{
    struct list_capt_s *prev_catpure = capture;
    while (capture)
    {
        if (capture->next)
        {
            free(capture->tag);
        }
        prev_catpure = capture;
        capture = capture->next;
        free(prev_catpure);
    }
}

struct list_capt_s *list_capt_init(void)
{
    struct list_capt_s *capture = malloc(sizeof(struct list_capt_s));
    capture->next = NULL;
    capture->tag = NULL;
    return capture;
}