#pragma once

#include <parser/parser.h>
#include <parser/ast/ast.h>

bool read_ini_file(struct parser *p);

bool read_sections(struct parser *p);
struct ast_section
{
    char *identifier;
};
struct ast_node *ast_section_init(enum ast_node_type type, void *data);


bool read_key_value(struct parser *p);
struct ast_key_value
{
    char *id;
    char *value;
};
struct ast_node *ast_key_value_init(enum ast_node_type type, void *data);

bool read_value(struct parser *p);

bool read_identifier(struct parser *p);

bool read_spaces(struct parser *p);

bool read_end_of_line(struct parser *p);

bool read_spacing(struct parser *p);

bool readassign(struct parser *p);
struct ast_assign
{
    char *id;
    char *num;
};
struct ast_node *ast_assign_init(enum ast_node_type type, void *data);


//Terminale rules
bool read_word(struct parser *p);

bool read_assignment_word(struct parser *p);

bool read_heredoc(struct parser *p);
struct ast_node *ast_heredoc_init(enum ast_node_type type, void *data);

bool read_ionumber(struct parser *p);

// Functional rules
bool read_input(struct parser *p);
struct ast_input{char *elt;};

bool read_list(struct parser *p);
struct ast_list{char *elt;};

bool read_and_or(struct parser *p);
struct ast_and_or{char *elt;};

bool read_pipeline(struct parser *p);
struct ast_pipeline {
    bool is_negative;
};

bool read_command(struct parser *p);
struct ast_command{char *elt;};

bool read_simple_command(struct parser *p);
struct ast_simple_command{char *elt;};

bool read_shell_command(struct parser *p);
struct ast_shell_command{char *elt;};

bool read_funcdec(struct parser *p);
struct ast_funcdec {
    char *function;
};

bool read_redirection(struct parser *p);
struct ast_redirection
{
    char *ionumber;
    char *redirect;
    char *word;
    char *heredoc;
};
struct ast_node *ast_redirection_init(char *ionumber, char *redirect, 
                                        char *word, char *heredoc);

bool read_prefix(struct parser *p);
struct ast_prefix{char *elt;};

bool read_element(struct parser *p);
struct ast_element{char *elt;};

bool read_compound_list(struct parser *p);
struct ast_compound_list{char *elt;};

// Key word rules
bool read_rule_for(struct parser *p);
struct ast_rule_for{char *elt;};

bool read_rule_while(struct parser *p);
struct ast_rule_while{char *elt;};

bool read_rule_until(struct parser *p);
struct ast_until{char *elt;};

bool read_rule_case(struct parser *p);
struct ast_case{char *elt;};

bool read_rule_if(struct parser *p);
struct ast_if{char *elt;};

bool read_rule_else_clause(struct parser *p);
struct ast_else_clause{char *elt;};

bool read_do_group(struct parser *p);
struct ast_do_group{char *elt;};

bool read_case_clause(struct parser *p);
struct ast_case_clause{char *elt;};

bool read_case_item(struct parser *p);
struct ast_case_item{char *elt;};