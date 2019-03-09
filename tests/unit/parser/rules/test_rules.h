#pragma once
#include "../../test.h"
#include <parser/rules/rules.h>
#include "helper_rules.h"

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


//Test functional
void test_read_and_or(void);
void test_read_pipeline(void);
void test_read_redirection(void);
void test_read_command(void);
void test_read_simple_command(void);
void test_read_prefix(void);
void test_read_element(void);
void test_funcdec(void);
void test_read_compound_list(void);