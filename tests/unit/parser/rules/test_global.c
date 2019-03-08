#include "test_rules.h"

void test_global(void)
{
    const size_t MAX_SIZE_PATH = 1024;
    char buff_path[MAX_SIZE_PATH];
    char *file = strdup(__FILE__);
    strcpy(buff_path, dirname(file));
    free(file);
    const char *FILE_NAME = strcat(buff_path, "/../data/config.ini");

    FILE *inifile = fopen(FILE_NAME, "r");

    if (!inifile)
    {
        printf("Error when trying to open file [%s]\n", FILE_NAME);
        assert(0);
        return;
    }

    fseek(inifile, 0, SEEK_END);
    long fsize = ftell(inifile);
    fseek(inifile, 0, SEEK_SET);
    char *content = malloc(fsize + 1);
    fread(content, fsize, 1, inifile);
    fclose(inifile);
    content[fsize] = 0;

    struct parser *p = parser_new_from_string(content);
    // parse
    if (!read_ini_file(p))
    {
        printf("Parsing failed at %d\n", p->cursor);
        switch (p->error->type)
        {
            case ON_CHAR:
                printf("expected char '%c'\n", p->error->u.c);
                break;
            case ON_TEXT:
                printf("expected text \"%s\"\n", p->error->u.text);
                break;
            case ON_RANGE:
                printf("expected range \"%d to %d\"\n",
                    p->error->u.range.begin, p->error->u.range.begin);
                break;
            case ON_INSET:
                printf("expected inset \"%s\"\n", p->error->u.inset);
                break;
            case ON_OUTSET:
                printf("expected outset \"%s\"\n", p->error->u.outset);
                break;
        }
        assert(0 && "error reading ini file");
    }
    parser_free(p);
    free(content);
}