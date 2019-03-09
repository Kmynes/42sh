#include "unit/parser/rules/test_rules.h"

void test_read_prefix(void)
{
    assert(test_rule(read_prefix, "i=0",
        "prefix\n\t- assignment_word: -> key:i value:0"));
    assert(test_not_rule(read_prefix, "i = 0"));

    assert(test_rule(read_prefix, "2>test.sh", "prefix\n\t- redirection_2_>_test.sh"));
    assert(test_rule(read_prefix, "2<test.sh", "prefix\n\t- redirection_2_<_test.sh"));
    assert(test_rule(read_prefix, "2>>test.sh",
        "prefix\n\t- redirection_2_>>_test.sh"));
    assert(test_rule(read_prefix, "2<<END\necho toto\nEND",
        "prefix\n\t- redirection_2_<<_\necho toto\n"));
    assert(test_rule(read_prefix, "2<<-END\necho toto\nEND",
        "prefix\n\t- redirection_2_<<-_\necho toto\n"));
    assert(test_rule(read_prefix, "2>&test.sh",
        "prefix\n\t- redirection_2_>&_test.sh"));
    assert(test_rule(read_prefix, "2<&test.sh",
        "prefix\n\t- redirection_2_<&_test.sh"));
    assert(test_rule(read_prefix, "2>|test.sh",
        "prefix\n\t- redirection_2_>|_test.sh"));
    assert(test_rule(read_prefix, "2<>test.sh",
        "prefix\n\t- redirection_2_<>_test.sh"));
}