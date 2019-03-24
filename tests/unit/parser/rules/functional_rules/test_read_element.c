#include "unit/parser/rules/test_rules.h"

void test_read_element(void)
{
    bool check = test_rule(read_element, "`abc`", "AST_ELEMENT(1)_`abc`");
    print_state_test(check, "test_read_element (1)");

    test_rule(read_element, "2>test.sh",
        "AST_ELEMENT(1)");
    check = test_rule(read_element, "2<test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (2)");
    check = test_rule(read_element, "2>>test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (3)");

    check = test_rule(read_element, "2<<END\necho toto\nEND",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (4)");

    check = test_rule(read_element, "2<<-END\necho toto\nEND",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (5)");

    check = test_rule(read_element, "2>&test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (6)");

    check = test_rule(read_element, "2<&test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (7)");

    check = test_rule(read_element, "2>|test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (8)");

    check = test_rule(read_element, "2<>test.sh",
                     "AST_ELEMENT(1)");
    print_state_test(check, "test_read_element (9)");
}