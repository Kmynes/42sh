#include "unit/parser/rules/test_rules.h"

void test_read_ini_file(void)
{
    char *text = " [les123]";
    char *text2 = ";je test\n[les123];id\nR = 43R33\n";
    char *text3 = ";The spacing\n[identifier];char\nstr = 'value'\n";
    char *text4 = ";An other spacing\n[id];int\ni = 200\n";

    struct parser *p = parser_new_from_string(text);
 
    bool check = !read_ini_file(p); // Suppose not match
    print_state_test(check, "test_read_ini_file (1)");
    parser_free(p);

    p = parser_new_from_string(text2);

    check = read_ini_file(p);
    print_state_test(check, "test_read_ini_file (2)");
    parser_free(p);

    p = parser_new_from_string(text3);
    check = read_ini_file(p);
    print_state_test(check, "test_read_ini_file (3)");
    parser_free(p);

    p = parser_new_from_string(text4);
    check = read_ini_file(p);
    print_state_test(check, "test_read_ini_file (4)");
    parser_free(p);
}