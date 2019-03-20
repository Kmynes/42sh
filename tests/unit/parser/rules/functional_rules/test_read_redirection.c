#include "unit/parser/rules/test_rules.h"

void test_read_redirection(void)
{
    bool check = test_not_rule(read_redirection, "not a redirection");
    print_state_test(check, "test_read_redirection (1)");

    check = test_rule(read_redirection, "2>test.sh",
        "AST_REDIRECTION(0)_2_>_test.sh");
    print_state_test(check, "test_read_redirection (2)");

    check = test_rule(read_redirection, "2<test.sh",
        "AST_REDIRECTION(0)_2_<_test.sh");
    print_state_test(check, "test_read_redirection (3)");

    check = test_rule(read_redirection, "2>>test.sh",
        "AST_REDIRECTION(0)_2_>>_test.sh");
    print_state_test(check, "test_read_redirection (4)");

    check = test_rule(read_redirection, "2<<END\necho toto\nEND",
        "AST_REDIRECTION(0)_2_<<_\necho toto\n");
    print_state_test(check, "test_read_redirection (5)");

    check = test_rule(read_redirection, "2<<-END\necho toto\nEND",
        "AST_REDIRECTION(0)_2_<<-_\necho toto\n");
    print_state_test(check, "test_read_redirection (6)");

    check = test_rule(read_redirection, "2>&test.sh",
        "AST_REDIRECTION(0)_2_>&_test.sh");
    print_state_test(check, "test_read_redirection (7)");
 
    check = test_rule(read_redirection, "2<&test.sh",
        "AST_REDIRECTION(0)_2_<&_test.sh");
    print_state_test(check, "test_read_redirection (8)");

    check = test_rule(read_redirection, "2>|test.sh",
        "AST_REDIRECTION(0)_2_>|_test.sh");
    print_state_test(check, "test_read_redirection (9)");

    check = test_rule(read_redirection, "2<>test.sh",
        "AST_REDIRECTION(0)_2_<>_test.sh");
    print_state_test(check, "test_read_redirection (10)");
}