#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <execution/builtins/builtins.h>
#include "exec.h"

/**
 * execute command using fork/execvpe
 * execvpe looks up the PATH before executing a command
 * @param cmd
 * @param env
 * @return
 */
int run_cmd(char **cmd, char **env)
{
    pid_t pid = fork();
    if (pid == -1)
        errx(1, "cannot do fork : an error occured, pid == -1");

    if (pid == 0)
    {
        // child
        execvpe(cmd[0], cmd, env);
        errx(127, "%s: not found", cmd[0]);
    }
    else
    {
        // father
        int status = 0;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
}

/**
 * execute a cmd by checking builtins or forking
 * @param cmd
 * @param env
 * @return
 */
int exec_cmd(char **cmd, char **env)
{
    int (*func)(char **args) = get_builtin(cmd[0]);

    if (func)
    {
        return func(cmd);
    }

    return run_cmd(cmd, env);
}