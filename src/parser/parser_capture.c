#include "parser.h"

char *extract_string(char *s, int begin, int end)
{
    char *extract = malloc(end - begin + 1);

    strncpy(extract, s + begin, end - begin);
    extract[end - begin] = '\0';

    return extract;
}

/**
** \brief debug function : print a capture
** \param p
** \param capture
*/
void print_capture(struct parser *p, struct list_capt_s *capture)
{
    int begin = capture->capt.begin;
    int end = capture->capt.end;
    char *value = extract_string(p->input, begin, end);
    printf("%s is %s\n", capture->tag, value);
    free(value);
}

/**
** store a capture_s and a tag in the list_capt_s
** caution : the last element of the list is initialized
** but is empty and contains no value
** this is because the list has no head
** \param capture
** \param tag
** \param capt_s
*/

struct list_capt_s *list_capt_store(struct list_capt_s *c, const char *tag,
    struct capture_s *capt_s)
{
    // let's store it at the beginning to get always the most recent first
    struct list_capt_s *capture = list_capt_init();
    capture->tag = strdup(tag);
    capture->capt = *capt_s;
    capture->next = c;

    return capture;
}

struct capture_s *list_capt_lookup(struct list_capt_s *capture,
    const char *tag)
{
    while (capture->next)
    {
        if (strcmp(capture->tag, tag) == 0)
            return &capture->capt;
        capture = capture->next;
    }

    return NULL;
}

void parser_remove_capture_by_tag(struct parser *p, const char *tag)
{
    struct list_capt_s *current = p->capture;
    struct list_capt_s *next;

    if (!current->next)
        return;

    // if capture is at the head of the list
    if (strcmp(current->tag, tag) == 0)
    {
        p->capture = current->next;
        free(current->tag);
        free(current);
        parser_remove_capture_by_tag(p, tag);
        return;
    }

    next = current->next;

    while (next->next)
    {
        if (strcmp(next->tag, tag) == 0)
        {
            current->next = next->next;
            free(next->tag);
            free(next);
            next = current->next;
            continue;
        }

        current = next;
        next = current->next;
    }
}