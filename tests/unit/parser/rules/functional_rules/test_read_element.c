#include "unit/parser/rules/test_rules.h"

void test_read_element(void)
{
    assert(test_rule(read_element, "`abc`", "AST_ELEMENT(1)_`abc`"));

    test_rule(read_element, "2>test.sh",
        "AST_ELEMENT(1)");
    assert(test_rule(read_element, "2<test.sh",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2>>test.sh",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2<<END\necho toto\nEND",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2<<-END\necho toto\nEND",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2>&test.sh",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2<&test.sh",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2>|test.sh",
                     "AST_ELEMENT(1)"));
    assert(test_rule(read_element, "2<>test.sh",
                     "AST_ELEMENT(1)"));
}