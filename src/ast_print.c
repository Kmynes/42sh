#include <libgen.h>
#include "ast_print.h"

/**
** \file ast_print.c
** \brief Contains functions related to printing the AST
** \author Yann
** \version v0.3
** \date March 2019
*/

int node_level = 0;

/**
** \brief This function removes any "(*)" pathern in strings
** \param input : the string from witch the patern will be removed from
*/
void remove_parenthesis(char *input)
{
    for (size_t i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '(')
        {
            size_t k = i;
            for (; input[k] != ')'; k++);

            k = k - i + 1;

            for (size_t z = i; input[z] != '\0'; z++)
                input[z] = input[z+k];
        }
    }
}

/**
** \brief This function removes the first four chars at the begening strings
** \param input : the string from witch the patern will be removed from
*/
void remove_start(char *input)
{
    for (size_t i = 0; input[i+4] != '\0'; i++)
        input[i] = input[i+4];
}

/**
** \brief This function increment one of the table's element concidering input
** \param input : the tested input
** \param table : the table that will be changed
*/
void increment_in_table(int *table, struct ast_node *input)
{
    if (table == NULL)
        return;
    if (input == NULL)
        return;
    /*
    if(input->type == AST_NODE_EMPTY)
        table[0] = table[0]+1;

    if(input->type == AST_NODE_INI_FILE)
        table[0] = table[0]+1;

    if(input->type == AST_NODE_SECTION)
        table[0] = table[0]+1;

    if(input->type == AST_NODE_KEY_VALUE)
        table[0] = table[0]+1;

    if(input->type == AST_NODE_ASSIGN)
        table[0] = table[0]+1;

    if(input->type == AST_INPUT)
        table[0] = table[0]+1;

    if(input->type == AST_LIST)
        table[0] = table[0]+1;

    if(input->type == AST_AND_OR)
        table[0] = table[0]+1;

    if(input->type == AST_PIPELINE)
        table[0] = table[0]+1;

    if(input->type == AST_COMMAND)
        table[0] = table[0]+1;

    if(input->type == AST_SIMPLE_COMMAND)
        table[0] = table[0]+1;

    if(input->type == AST_SHELL_COMMAND)
        table[0] = table[0]+1;

    if(input->type == AST_FUNCDEC)
        table[0] = table[0]+1;

    if(input->type == AST_REDIRECTION)
        table[0] = table[0]+1;

    if(input->type == AST_PREFIX)
        table[0] = table[0]+1;

    if(input->type == AST_ELEMENT)
        table[0] = table[0]+1;

    if(input->type == AST_COMPOUND_LIST)
        table[0] = table[0]+1;

    if(input->type == AST_RULE_FOR)
        table[0] = table[0]+1;

    if(input->type == AST_RULE_WHILE)
        table[0] = table[0]+1;

    if(input->type == AST_RULE_UNTIL)
        table[0] = table[0]+1;

    if(input->type == AST_RULE_CASE)
        table[0] = table[0]+1;

    if(input->type == AST_RULE_IF)
        table[0] = table[0]+1;

    if(input->type == AST_ELSE_CLAUSE)
        table[0] = table[0]+1;

    if(input->type == AST_DO_GROUP)
        table[0] = table[0]+1;

    if(input->type == AST_CASE_CLAUSE)
        table[0] = table[0]+1;

    if(input->type == AST_CASE_ITEM)
        table[0] = table[0]+1;

    if(input->type == AST_HEREDOC)
        table[0] = table[0]+1;

    if(input->type == AST_ASSIGNEMENT_WORD)
        table[0] = table[0]+1;

    if(input->type == AST_WORD)
        table[0] = table[0]+1;
    */

}

/**
** \brief This function generates the DOT file
** \param ast: represents the ast that will be used to print into the dotfile
** \param stream: represents the file stream in which the data of the ast will
** be printed
*/
int ast_print(struct ast_node *ast, FILE *stream)
{
    //int *table[29] = {0};
    if (ast == NULL)
        return 1;

    int first_one = 0;

    if (stream == NULL)
    {
        char path[1024];
        getcwd(path, sizeof(path));
        strcat(path, "/doc/ast.dot");
        stream = fopen(path, "w");
        first_one = 1;
        ast = ast->children[0];

        if (stream == NULL)
            return 1;
    }

    if (first_one == 1)
        fprintf(stream, "digraph ast {\n");

    char *ast_string = ast->to_string(ast);
    remove_start(ast_string);
    remove_parenthesis(ast_string);

    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        char *ast_child_str = child->to_string(child);
        remove_start(ast_child_str);
        remove_parenthesis(ast_child_str);

        fprintf(stream, "\t\"%s%d\" -> \"%s%d\";\n", ast_string, node_level,
            ast_child_str, node_level + 1);
        free(ast_child_str);
        node_level++;
        ast_print(child, stream);
        node_level--;
    }

    free(ast_string);
    if (first_one == 1)
    {
        fprintf(stream, "}");
        fclose(stream);
    }

    return 0;
}