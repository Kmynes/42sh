#include "unit/parser/rules/test_rules.h"

void test_read_element(void)
{
    assert(test_rule(read_element, "`abc`", "element:`abc`"));

    assert(test_rule(read_element, "2>test.sh",
        "element\n\t- redirection_2_>_test.sh"));
    assert(test_rule(read_element, "2<test.sh",
        "element\n\t- redirection_2_<_test.sh"));
    assert(test_rule(read_element, "2>>test.sh",
        "element\n\t- redirection_2_>>_test.sh"));
    assert(test_rule(read_element, "2<<END\necho toto\nEND",
        "element\n\t- redirection_2_<<_\necho toto\n"));
    assert(test_rule(read_element, "2<<-END\necho toto\nEND",
        "element\n\t- redirection_2_<<-_\necho toto\n"));
    assert(test_rule(read_element, "2>&test.sh",
        "element\n\t- redirection_2_>&_test.sh"));
    assert(test_rule(read_element, "2<&test.sh",
        "element\n\t- redirection_2_<&_test.sh"));
    assert(test_rule(read_element, "2>|test.sh",
        "element\n\t- redirection_2_>|_test.sh"));
    assert(test_rule(read_element, "2<>test.sh",
        "element\n\t- redirection_2_<>_test.sh"));
}