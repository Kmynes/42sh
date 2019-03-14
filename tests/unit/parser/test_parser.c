#include "test_parser.h"
#include "rules/test_rules.h"

void test_rules(void) {
    //Terminal
    test_read_assign();
    test_read_word();
    test_read_assignment_word();
    test_read_ionumber();
    test_read_heredoc();
    test_read_eof();

    //Functional
    test_read_input();
    test_read_list();
    test_read_and_or();
    test_read_pipeline();
    test_read_command();
    test_read_simple_command();
    test_read_redirection();
    test_read_prefix();
    test_read_element();

    //Key word
    test_read_compound_list();
    test_read_rule_case();
    test_read_case_item();
    test_read_case_clause();
    test_read_rule_else_clause();
    test_read_do_group();
    test_read_rule_if();
    test_read_rule_until();
    test_read_rule_while();
    test_read_rule_for();
    test_read_shell_command();
    test_read_funcdec();
}

void test_parser(void)
{
    test_ast_data();
    test_ast_init();
    test_ast_accessor();
    test_parser_capture_init();
    test_parser_capture();
    test_parser_character();
    test_parser_init();
    test_parser_read_alphanum();
    test_parser_read_interval();
    test_parser_string_includes();
}

void test_suite_parser(void)
{
    test_parser();
    test_rules();
}