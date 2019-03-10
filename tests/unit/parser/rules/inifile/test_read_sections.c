#include "unit/parser/rules/test_rules.h"

void test_read_sections(void)
{
    char *text = " [les123]";
    char *text2 = ";je test\n[les123];id\nR = 43R33\n";

    struct parser *p = parser_new_from_string(text);
    struct parser *p2 = parser_new_from_string(text2);

    assert(!read_sections(p));
    //struct ast_node *ast = p->ast->children[0]->children[0]->children[0]; // Parser his ast - ast_ini_file - ast_section - ast_key_value
    assert(read_sections(p2));

    parser_free(p);
    parser_free(p2);
}