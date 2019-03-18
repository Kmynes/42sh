#include <parser/rules/rules.h>
#include <utils/assignment_word.h>
#include <utils/string.h>
#include <utils/function_utils.h>
#include <utils/exec.h>
#include <execution/builtins/builtins.h>
/**
** \file read_simple_command.c
** \brief reads simple_command grammar as specified by the subject.
**
** simple_command: (prefix)+ | (prefix)* (element)+
** \author Thibault
** \version 0.3
** \date February 2019
*/

static bool sub_command1(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (read_prefix(p))
    {
        ZERO_OR_MANY(parser_readeol(p));
        return true;
    }

    p->cursor = tmp;
    return false;
}

static bool read_simple_command1(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (ONE_OR_MANY(sub_command1(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);
        ast_set_in_parser(p, ast);

        return true;
    }

    p->cursor = tmp;
    return false;
}

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
        else if (sub_child->type == AST_REDIRECTION)
        {}

        child = ast->children[++i];
    }
    while (i < ast->nb_children && child->type == AST_PREFIX);
    return list;
}

static char **create_command_list(struct ast_node *ast, size_t prefix_count)
{
    struct ast_node *child = NULL;
    struct ast_node *sub_child = NULL;
    size_t len_args = ast->nb_children - prefix_count + 1;
    char **args = malloc(sizeof(char *) * len_args);

    size_t i = 0;
    size_t range = prefix_count;
    bool prog_found = false;
    while (range < ast->nb_children)
    {
        child = ast->children[range];
        sub_child = child->children[0];
        if (sub_child->type == AST_WORD)
        {
            if (!prog_found)
            {
                char *prog = sub_child->data;
                char delim[] = " ";
                char *part = strtok(prog, delim);
                while (part)
                {
                    if (i == len_args)
                        args = enlarge_list(args, &len_args);

                    args[i++] = part;
                    part = strtok(NULL, delim);
                }
                prog_found = true;
                range++;
            }
            else
            {
                if (i == len_args)
                    args = enlarge_list(args, &len_args);

                args[i++] = sub_child->data;
                range++;
            }
        }
    }
    args[i] = i == 0 ? "" : NULL;
    return args;
}

static int run_cmd(char **cmd, char **env)
{
    return exec_cmd(cmd, env);
}

int ast_simple_command_exec(struct ast_node *ast)
{
    if (ast->nb_children == 0)
        return 0;
    struct ast_assignment_word *list = create_env_list(ast);
    size_t prefix_count = assignment_word_list_len(list);
    char **args = create_command_list(ast, prefix_count);

    size_t count = 0;
    char **env = build_env_param(list, &count);
    int res = run_cmd(args, env);

    string_list_free(env, count);
    free(args);

    return res;
}

struct ast_node *ast_simple_command_init()
{
    struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
    ast->exec = ast_simple_command_exec;
    return ast;
}