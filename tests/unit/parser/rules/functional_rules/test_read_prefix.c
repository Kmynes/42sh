#include "unit/parser/rules/test_rules.h"

void test_read_prefix(void)
{
    test_rule(read_prefix, "i=0", "prefix\n\t- assignment_word: -> key:i value:0");
    test_not_rule(read_prefix, "i = 0");

    test_rule(read_prefix, "2>test.sh", "prefix\n\t- redirection_2_>_test.sh");
    test_rule(read_prefix, "2<test.sh", "prefix\n\t- redirection_2_<_test.sh");
    test_rule(read_prefix, "2>>test.sh", "prefix\n\t- redirection_2_>>_test.sh");
    test_rule(read_prefix, "2<<END\necho toto\nEND", "prefix\n\t- redirection_2_<<_\necho toto\n");
    test_rule(read_prefix, "2<<-END\necho toto\nEND", "prefix\n\t- redirection_2_<<-_\necho toto\n");
    test_rule(read_prefix, "2>&test.sh", "prefix\n\t- redirection_2_>&_test.sh");
    test_rule(read_prefix, "2<&test.sh", "prefix\n\t- redirection_2_<&_test.sh");
    test_rule(read_prefix, "2>|test.sh", "prefix\n\t- redirection_2_>|_test.sh");
    test_rule(read_prefix, "2<>test.sh", "prefix\n\t- redirection_2_<>_test.sh");
}