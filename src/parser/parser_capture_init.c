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

void parser_free_capture_list(struct parser *p)
{
    struct list_capt_s *current = p->capture;
    struct list_capt_s *next;

    while (current)
    {
        next = current->next;
        free(current->tag);
        free(current);
        current = next;
    }

    p->capture = list_capt_init();
}