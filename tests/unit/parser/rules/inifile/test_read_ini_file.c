#include "unit/parser/rules/test_rules.h"

void test_read_ini_file(void)
{
    char *text = " [les123]";
    char *text2 = ";je test\n[les123];id\nR = 43R33\n";
    char *text3 = ";The spacing\n[identifier];char\nstr = 'value'\n";
    char *text4 = ";An other spacing\n[id];int\ni = 200\n";

    struct parser *p = parser_new_from_string(text);
 
    assert(!read_ini_file(p)); // Suppose not match
    parser_free(p);

    p = parser_new_from_string(text2);

    assert(read_ini_file(p));
    parser_free(p);

    p = parser_new_from_string(text3);
    assert(read_ini_file(p));
    parser_free(p);

    p = parser_new_from_string(text4);
    assert(read_ini_file(p));
    parser_free(p);
}