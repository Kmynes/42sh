#include <parser/parser.h>


bool read_ini_file(struct parser *p);

bool read_sections(struct parser *p);

bool read_key_value(struct parser *p);

bool read_value(struct parser *p);

bool read_identifier(struct parser *p);

bool read_spaces(struct parser *p);

bool read_end_of_line(struct parser *p);

bool read_spacing(struct parser *p);

bool parser_readassign(struct parser *p);

//Terminale rules
bool read_word(struct parser *p);


// Functional rules
bool read_and_or(struct parser *p);

bool read_pipeline(struct parser *p);

bool read_command(struct parser *p);

bool read_simple_command(struct parser *p);

bool read_shell_command(struct parser *p);

bool read_funcdec(struct parser *p);

bool read_redirection(struct parser *p);

bool read_prefix(struct parser *p);

bool read_element(struct parser *p);

bool read_copound_list(struct parser *p);

// Key word rules

bool read_rule_for(struct parser *p);

bool read_rule_while(struct parser *p);

bool read_rule_until(struct parser *p);

bool read_rule_case(struct parser *p);

bool read_rule_if(struct parser *p);

bool read_rule_else_clause(struct parser *p);

bool read_do_group(struct parser *p);

bool read_case_clause(struct parser *p);

bool read_case_item(struct parser *p);