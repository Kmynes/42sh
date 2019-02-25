#include "test_rules.h"

void test_read_end_of_line(void)
{
    char *str = "philippe\nviens\r\nenc";
    struct parser *p = parser_new_from_string(str);

    for (size_t i = 0 ; i < strlen(str) ; i++)
    {
        if(i == 8)
        {
            assert(parser_readeol(p));
            assert(p->cursor == 9);
        }
        else if (i == 14)
        {
            assert(parser_readeol(p));
            assert(p->cursor == 16);
            i++;
        }
        else
        {
            assert(!parser_readeol(p));
            assert(p->cursor == (int)i);
            p->cursor++;
        }
    }
    parser_free(p);
}