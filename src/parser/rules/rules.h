#pragma once

#include <parser/parser.h>
#include <parser/ast/ast.h>

//Global
char *default_to_string(struct ast_node *ast, char *type);
struct ast_multiple_word
{
    char **words;
    size_t nb_word;
    size_t capacity;
};
bool read_multiple_word(struct parser *p, struct ast_multiple_word *data);

bool read_ini_file(struct parser *p);
struct ast_node *ast_ini_file_init();

bool read_sections(struct parser *p);
struct ast_section
{
    char *identifier;
};
struct ast_node *ast_section_init(struct ast_section *data);

bool read_key_value(struct parser *p);
struct ast_key_value
{
    char *id;
    char *value;
};
struct ast_node *ast_key_value_init(struct ast_key_value *data);

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

// Terminal rules
bool read_word(struct parser *p);
struct ast_node *ast_word_init(void *data);

bool read_assignment_word(struct parser *p);
struct ast_assignment_word
{
    char *key;
    char *value;
    struct ast_assignment_word *next;
};
struct ast_node *ast_assignment_word_init(struct ast_assignment_word *data);

bool read_heredoc(struct parser *p);
struct ast_node *ast_heredoc_init(void *data);

bool read_ionumber(struct parser *p);

bool read_eof(struct parser *p);

// Functional rules
bool read_input(struct parser *p);
struct ast_node *ast_input_init();

bool read_list(struct parser *p);
struct ast_node *ast_list_init();

bool read_and_or(struct parser *p);
struct ast_node *ast_and_or_init();

bool read_pipeline(struct parser *p);
struct ast_pipeline
{
    bool is_negative;
};
struct ast_node *ast_pipeline_init(void *data);
char *ast_pipeline_to_string(struct ast_node *ast);
void ast_pipeline_free(void *data);

bool read_command(struct parser *p);
struct ast_node *ast_command_init();

bool read_simple_command(struct parser *p);
struct ast_node *ast_simple_command_init();

bool read_shell_command(struct parser *p);
struct ast_node *ast_shell_command_init();

bool read_funcdec(struct parser *p);
struct ast_funcdec 
{
    char *function;
};
struct ast_node *ast_funcdec_init(void *data);

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
struct ast_node *ast_prefix_init();

bool read_element(struct parser *p);
struct ast_node *ast_element_init();

bool read_compound_list(struct parser *p);
struct ast_node *ast_compound_list_init();

// Key word rules
bool read_rule_for(struct parser *p);

struct ast_node *ast_rule_for_init(struct ast_multiple_word *data);

bool read_rule_while(struct parser *p);
struct ast_rule_while
{
    char *elt;
};
struct ast_node *ast_rule_while_init();

bool read_rule_until(struct parser *p);
struct ast_until
{
    char *elt;
};
struct ast_node *ast_rule_until_init();

bool read_rule_case(struct parser *p);
struct ast_case
{
    char *elt;
};
struct ast_node *ast_rule_case_init();

bool read_rule_if(struct parser *p);
struct ast_if
{
    char *elt;
};
struct ast_node *ast_rule_if_init();

bool read_rule_else_clause(struct parser *p);
struct ast_else_clause
{
    char *elt;
};
struct ast_node *ast_else_clause_init();

bool read_do_group(struct parser *p);
struct ast_do_group
{
    char *elt;
};
struct ast_node *ast_do_group_init();

bool read_case_clause(struct parser *p);
struct ast_case_clause
{
    char *elt;
};
struct ast_node *ast_case_clause_init();

bool read_case_item(struct parser *p);
struct ast_node *ast_case_item_init(struct ast_multiple_word *data);

char *default_to_string(struct ast_node *ast, char *type);
char *ast_default_to_string(struct ast_node *ast);
void ast_default_print(struct ast_node *ast);
