#include "test_parser.h"
#include "rules/test_rules.h"

void test_rules(void)
{
    //Ini file
    test_read_ini_file();
    test_read_sections();
    test_read_key_value();
    test_read_value();
    test_read_identifier();
    test_read_spaces();
    test_read_end_of_line();
    test_read_spacing();
    test_global();

    //Terminal
    test_read_assign();
    test_read_word();
    test_read_assignment_word();
    test_read_ionumber();
    test_read_heredoc();

    //Functional
    test_read_redirection();
    test_read_prefix();
    test_read_element();
    test_read_simple_command();
    test_read_pipeline();
    test_read_command();
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
//    test_parser();
    test_rules();
}