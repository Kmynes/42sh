#include "unit/parser/rules/test_rules.h"

void test_read_element(void)
{
    test_rule(read_element, "`abc`", "read_element: -> element:`abc`");

    test_rule(read_element, "2>test.sh", 
        "read_element\n\t- redirection_2_>_test.sh");
    test_rule(read_element, "2<test.sh", 
        "read_element\n\t- redirection_2_<_test.sh");
    test_rule(read_element, "2>>test.sh", 
        "read_element\n\t- redirection_2_>>_test.sh");
    test_rule(read_element, "2<<END\necho toto\nEND",
        "read_element\n\t- redirection_2_<<_\necho toto\n");
    test_rule(read_element, "2<<-END\necho toto\nEND",
        "read_element\n\t- redirection_2_<<-_\necho toto\n");
    test_rule(read_element, "2>&test.sh", 
        "read_element\n\t- redirection_2_>&_test.sh");
    test_rule(read_element, "2<&test.sh", 
        "read_element\n\t- redirection_2_<&_test.sh");
    test_rule(read_element, "2>|test.sh", 
        "read_element\n\t- redirection_2_>|_test.sh");
    test_rule(read_element, "2<>test.sh", 
        "read_element\n\t- redirection_2_<>_test.sh");
}