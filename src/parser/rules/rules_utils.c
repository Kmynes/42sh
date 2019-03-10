#include "rules.h"

bool read_multiple_word(struct parser *p, struct ast_multiple_word *data)
{
    unsigned int tmp = p->cursor;
    char buff[64];
    sprintf(buff, "multiple_word_%ld", data->nb_word);

    if (parser_begin_capture(p, buff)
       && read_word(p)
       && parser_end_capture(p, buff))
    {
        if (data->nb_word == data->capacity)
        {
            size_t new_size = sizeof(char) * data->capacity * 2;
            void *ptr = realloc(data->words, new_size);
            if (!ptr)
            {
                //Catch this error
                return false;
            }

            data->words = ptr;
            data->capacity *= 2;
        }

        data->words[data->nb_word] = parser_get_capture(p, buff);
        data->nb_word++;
        return true;
    }

    p->cursor = tmp;
    return false;
}