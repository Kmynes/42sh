#include <parser/rules/rules.h>

static bool read_simple_command1(struct parser *p)
{
    unsigned int tmp = p->cursor;
    if (ONE_OR_MANY(read_prefix(p)))
    {
        struct ast_node *ast = ast_simple_command_init();
        ast_recover_all_from_parser(ast, p, AST_PREFIX);

        if (ONE_OR_MANY(read_element(p)))
            ast_recover_all_from_parser(ast, p, AST_ELEMENT);

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

    p->cursor = tmp;
    return false;
}

bool read_simple_command(struct parser *p)
{
    return read_simple_command1(p) || read_simple_command2(p);
}

void add_assignment_word(struct ast_assignment_word *list, 
    void *data)
{
    while (list->next != NULL)
        list = list->next;
    list->next = data;
}

char **build_env_param(struct ast_assignment_word *list, size_t *count)
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

int run_cmd(char **cmd, char **env)
{
    pid_t pid = fork();
    if (pid == -1)
        errx(1, "cannot do fork : an error occured, pid == -1");

    if (pid == 0)
    { // child
        execvpe(cmd[0], cmd, env);
        errx(1, "cannot execve: an error occured");
    }
    else
    { // father
        int status = 0;
        waitpid(pid, &status, 0);

        return status;
    }
}

int ast_simple_command_exec(struct ast_node *ast)
{
    struct ast_node *child = NULL;
    struct ast_node *sub_child = NULL;
    struct ast_assignment_word *list = NULL;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        child = ast->children[i];
        if (child->type == AST_PREFIX)
        {
            sub_child = child->children[0];
            if (sub_child->type == AST_ASSIGNEMENT_WORD)
            {
                if (list == NULL)
                    list = sub_child->data; 
                else
                    add_assignment_word(list, sub_child->data);
            }
            else if(sub_child->type == AST_REDIRECTION)
            {

            }
        }
        else if(child->type == AST_ELEMENT)
        {
            sub_child = child->children[0];
            if (sub_child->type == AST_WORD)
            {
                char *args[2];
                args[0] = sub_child->data;
                args[1] = NULL;
                size_t count = 0;
                char **env = build_env_param(list, &count);
                run_cmd(args, env);

                for (size_t j=0;j < count; j++)
                    free(env[j]);
                free(env);
            }
        }
    }

    return 0;
}

struct ast_node *ast_simple_command_init()
{
    struct ast_node *ast = ast_init(AST_SIMPLE_COMMAND, NULL);
    ast->exec = ast_simple_command_exec;
    return ast;
}