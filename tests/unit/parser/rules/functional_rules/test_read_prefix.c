#include "unit/parser/rules/test_rules.h"

void test_read_prefix(void)
{
    assert(test_rule(read_prefix, "i=0",
        "AST_PREFIX(1)"));
    assert(test_not_rule(read_prefix, "i = 0"));

    assert(test_rule(read_prefix, "2>test.sh", "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2<test.sh", "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2>>test.sh",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2<<END\necho toto\nEND",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2<<-END\necho toto\nEND",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2>&test.sh",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2<&test.sh",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2>|test.sh",
                     "AST_PREFIX(1)"));
    assert(test_rule(read_prefix, "2<>test.sh",
                     "AST_PREFIX(1)"));
}