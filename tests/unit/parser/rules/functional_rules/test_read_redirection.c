#include "unit/parser/rules/test_rules.h"

void test_read_redirection(void)
{
    test_not_rule(read_redirection, "not a redirection");
    test_rule(read_redirection, "2>test.sh", "redirection_2_>_test.sh");
    test_rule(read_redirection, "2<test.sh", "redirection_2_<_test.sh");
    test_rule(read_redirection, "2>>test.sh", "redirection_2_>>_test.sh");
    test_rule(read_redirection, "2<<END\necho toto\nEND",
        "redirection_2_<<_\necho toto\n");
    test_rule(read_redirection, "2<<-END\necho toto\nEND",
        "redirection_2_<<-_\necho toto\n");
    test_rule(read_redirection, "2>&test.sh", "redirection_2_>&_test.sh");
    test_rule(read_redirection, "2<&test.sh", "redirection_2_<&_test.sh");
    test_rule(read_redirection, "2>|test.sh", "redirection_2_>|_test.sh");
    test_rule(read_redirection, "2<>test.sh", "redirection_2_<>_test.sh");
}