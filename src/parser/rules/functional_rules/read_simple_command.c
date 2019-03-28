#include <parser/rules/rules.h>
#include <utils/assignment_word.h>
#include <utils/string.h>
#include <utils/function_utils.h>
#include <utils/exec.h>
#include <execution/builtins/builtins.h>
#include <fcntl.h>

/**
** \file read_simple_command.c
** \brief reads simple_command grammar as specified by the subject.
**
** simple_command: (prefix)+ | (prefix)* (element)+
** \author Thibault
** \version 0.3
** \date February 2019
*/

/*
** \brief Allow to read the first part of the simple_command's grammar
**  (prefix)+
** \param parser
** \return true if this part is can be read on the current parsor's cursor
** false otherwise
*/
static bool read_simple_command1(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (ONE_OR_MANY(read_prefix(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);
        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;
    return false;
}

/*
** \brief Allow to read the second part of the simple_command's grammar
**  (prefix)* (element)+
** \param parser
** \return true if this part is readable from the current parsor's cursor
** false otherwise
*/
static bool read_simple_command2(struct parser *p)
{
    unsigned int tmp = p->cursor;

    if (ZERO_OR_MANY(read_prefix(p)) && ONE_OR_MANY(read_element(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);
        ast_recover_all_from_parser(ast, p, AST_ELEMENT);

        ast_set_in_parser(p, ast);
        return true;
    }

    ast_delete_all_from_parser(p, AST_PREFIX);

    p->cursor = tmp;
    return false;
}


bool read_simple_command(struct parser *p)
{
    return read_simple_command2(p) || read_simple_command1(p);
}

/**
** \brief generates env params from chained list to string array
** \param list
** \param count
** \return
*/
static char **build_env_param(struct ast_assignment_word *list, size_t *count)
{
    struct ast_assignment_word *tmp = list;
    while (tmp)
    {
        *count += 1;
        tmp = tmp->next;
    }

    char **env = malloc(sizeof(char*)*((*count) + 1));
    env[*count] = NULL;
    size_t i = 0;
    while (list)
    {
        size_t size = sizeof(char) * (strlen(list->key) + strlen(list->value));
        char *var = malloc(size + 2);

        strcpy(var, list->key);
        strcat(var, "=");
        strcat(var, list->value);

        env[i++] = var;
        list = list->next;
    }

    return env;
}

/**
** \brief generates list of env variables to feed to the command
** \param ast
** \return Create the environment variables for the sub process
*/
static struct ast_assignment_word *create_env_list(struct ast_node *ast)
{
    struct ast_node *sub_child = NULL;
    struct ast_assignment_word *list = NULL;
    struct ast_node *child = ast->children[0];

    size_t i = 0;
    do
    {
        sub_child = child->children[0];
        if (sub_child->type == AST_ASSIGNEMENT_WORD)
        {
            if (list == NULL)
                list = sub_child->data;
            else
                add_assignment_word(list, sub_child->data);
        }

        child = ast->children[++i];
    }
    while (i < ast->nb_children && child->type == AST_PREFIX);
    return list;
}

/*
** \brief generates command from ast children, matches only AST_WORD
** \param ast
** \param prefix_count
** \param prog_found
** \return list of environment variables char **env
*/
static char **create_command_list(struct ast_node *ast, size_t prefix_count,
    bool *prog_found, size_t *nb_args)
{
    struct ast_node *child = NULL;
    struct ast_node *sub_child = NULL;
    size_t len_args = ast->nb_children - prefix_count + 1;
    char **args = malloc(sizeof(char *) * len_args);

    *nb_args = 0;
    size_t i = 0;
    size_t range = prefix_count;

    for  (;range < ast->nb_children; i++)
    {
        child = ast->children[range];
        sub_child = child->children[0];
        if (sub_child->type == AST_WORD)
        {

            char *word = strdup(sub_child->data);
            manage_variable_str(&word, true);
            if (!*prog_found)
            {
                char *prog = word;
                char delim[] = " ";
                char *part = strtok(prog, delim);
                while (part)
                {
                    if (i == len_args)
                        args = enlarge_list(args, &len_args);

                    args[i] = strdup(part);
                    *nb_args += 1;
                    part = strtok(NULL, delim);
                }
                *prog_found = true;
            }
            else
            {
                if (i == len_args)
                    args = enlarge_list(args, &len_args);

                args[i] = strdup(word);
                range++;
                *nb_args += 1;
            }
            free(word);
        }
        range++;
    }

    args[*nb_args] = NULL;
    return args;
}

/*
** \brief Create a redirection
** \param ast
** \return 0 in all case
*/
int create_redirection(struct ast_redirection *redir)
{
    if (strcmp(redir->redirect, ">") == 0)
    {
        int fd = open(redir->word,
                      O_RDWR | O_CREAT, 0666);
        dup2(fd, STDOUT_FILENO);
    }
    else if (strcmp(redir->redirect, ">>") == 0)
    {
        int fd = open(redir->word,
                      O_RDWR | O_APPEND, 0666);
        dup2(fd, STDOUT_FILENO);
    }
    else if (strcmp(redir->redirect, "<") == 0)
    {
        int fd = open(redir->word,
                      O_RDWR | O_APPEND, 0666);
        dup2(fd, STDIN_FILENO);
    }
    else if (strcmp(redir->redirect, "<") == 0)
    {
        int fd = open(redir->word,
                      O_RDWR | O_APPEND, 0666);
        dup2(fd, STDIN_FILENO);
    }
    else if (strcmp(redir->redirect, "<<") == 0)
    {
        char *filename = "/tmp/42sh_redirection";
        int fd = open(filename, O_RDWR | O_CREAT, 0666);
        write(fd, redir->heredoc, strlen(redir->heredoc));
        fd = open(filename,
                      O_RDWR | O_APPEND, 0666);
        dup2(fd, STDIN_FILENO);
    }

    return 0;
}

int create_redirections(struct ast_node *ast)
{
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        struct ast_node *child = ast->children[i];
        if (child->children[0]->type == AST_REDIRECTION)
        {
            struct ast_redirection *data = child->children[0]->data;
            create_redirection(data);
        }
    }

    return 0;
}

/**
** \brief executes ast simple command, generates command string, env params
** and call the fork exec function
** \param ast
** \return the result of the code of the sub program
**/
int ast_simple_command_exec(struct ast_node *ast)
{
    struct ast_assignment_word *list = create_env_list(ast);
    size_t prefix_count = assignment_word_list_len(list);

    int res = 0;
    bool has_prog = false;
    size_t nbr_args;
    char **args = create_command_list(ast, prefix_count, &has_prog, &nbr_args);
    if (has_prog)
    {
        struct list_func *func = get_function(args[0]);
        if (func)
        {
            struct ast_node *ast_funcdec = func->ast_funcdec;
            ast_funcdec->exec(ast_funcdec);
        }
        else
        {
            size_t count = 0;
            char **env = build_env_param(list, &count);
            create_redirections(ast);
            res = exec_cmd(args, env);
            string_list_free(env, count);
        }
    }

    string_list_free(args, nbr_args);

    return res;
}

struct ast_node *ast_simple_command_init(void)
{
    struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
    ast->exec = ast_simple_command_exec;
    return ast;
}