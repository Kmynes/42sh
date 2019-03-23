#include "unit/parser/rules/test_rules.h"

void test_read_prefix(void)
{
    bool check = test_rule(read_prefix, "i=0",
        "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (1)");

    check = test_not_rule(read_prefix, "i = 0");
    print_state_test(check, "test_read_prefix (2)");

    check = test_rule(read_prefix, "2>test.sh", "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (3)");

    check = test_rule(read_prefix, "2<test.sh", "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (4)");

    check = test_rule(read_prefix, "2>>test.sh",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (5)");

    check = test_rule(read_prefix, "2<<END\necho toto\nEND",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (6)");

    check = test_rule(read_prefix, "2<<-END\necho toto\nEND",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (7)");

    check = test_rule(read_prefix, "2>&test.sh",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (8)");

    check = test_rule(read_prefix, "2<&test.sh",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (9)");

    check = test_rule(read_prefix, "2>|test.sh",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (10)");

    check = test_rule(read_prefix, "2<>test.sh",
                     "AST_PREFIX(1)");
    print_state_test(check, "test_read_prefix (11)");
}