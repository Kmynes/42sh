#include "rules.h"

char *extract_string(char *s, int begin, int end)
{
    char *extract = malloc(end - begin + 1);

    strncpy(extract, s + begin, end - begin);
    extract[end - begin] = '\0';

    return extract;
}

/**
 * debug function : print a capture
 * @param p
 * @param capture
 */
void print_capture(struct parser *p, struct list_capt_s *capture)
{
    int begin = capture->capt.begin;
    int end = capture->capt.end;
    char *value = extract_string(p->input, begin, end);
    printf("%s is %s\n", capture->tag, value);
    free(value);
}

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
    return capture;
}

/**
 * store a capture_s and a tag in the list_capt_s
 * caution : the last element of the list is initialized
 * but is empty and contains no value
 * this is because the list has no head
 * @param capture
 * @param tag
 * @param capt_s
 */

void list_capt_store(struct list_capt_s *capture, const char *tag, struct capture_s *capt_s)
{
    while(capture->next != NULL)
    {
        capture = capture->next;
    }

    capture->tag = strdup(tag);
    capture->capt = *capt_s;
    capture->next = list_capt_init();
}

struct capture_s *list_capt_lookup(struct list_capt_s *capture, const char *tag)
{
    while (capture->next)
    {
        if (strcmp(capture->tag, tag) == 0) {
            return &capture->capt;
        }
        capture = capture->next;
    }

    return NULL;
}


bool parser_readassign(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (parser_begin_capture(p, "id") && parser_readidentifier(p)
        && parser_end_capture(p, "id") && parser_readchar(p, '=')
        && parser_begin_capture(p, "num") && parser_readinteger(p) 
        && parser_end_capture(p, "num"))
    {
        char *id = parser_get_capture(p, "id");
        char *num = parser_get_capture(p, "num");
        struct ast_assign ast = {id, num};
        ast_store(p, AST_NODE_ASSIGN, &ast);
        return true;
    }

    p->cursor = tmp;
    return false;
}