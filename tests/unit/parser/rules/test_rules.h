#pragma once

#include <parser/rules/rules.h>
#include "helper_rules.h"
#include "../../test.h"

//Test inifile
void test_read_ini_file(void);
void test_read_sections(void);
void test_read_key_value(void);
void test_read_value(void);
void test_read_identifier(void);
void test_read_spaces(void);
void test_read_end_of_line(void);
void test_read_spacing(void);
void test_global(void);

//Test terminal
void test_read_assign(void);
void test_read_word(void);
void test_read_assignment_word(void);
void test_read_ionumber(void);
void test_read_heredoc(void);
void test_read_eof(void);

//Test functional
void test_read_input(void);
void test_read_list(void);
void test_read_and_or(void);
void test_read_pipeline(void);
void test_read_redirection(void);
void test_read_command(void);
void test_read_simple_command(void);
void test_read_prefix(void);
void test_read_element(void);
void test_read_funcdec(void);

//Test key word
void test_read_compound_list(void);
void test_read_rule_case(void);
void test_read_case_item(void);
void test_read_case_clause(void);
void test_read_rule_else_clause(void);
void test_read_do_group(void);
void test_read_rule_if(void);
void test_read_rule_until(void);
void test_read_rule_while(void);
void test_read_rule_for(void);
void test_read_shell_command(void);
