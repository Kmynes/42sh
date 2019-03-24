#pragma once

#include <stdbool.h>
#include <parser/rules/rules.h>
#include "helper_rules.h"
#include "../../test.h"

// Test terminal
void test_read_assign(void);
void test_read_word(void);
void test_read_assignment_word(void);
void test_read_ionumber(void);
void test_read_heredoc(void);
void test_read_eof(void);
void test_read_comment(void);

// Test functional
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

// Test key word
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