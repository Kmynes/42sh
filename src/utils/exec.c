#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include "exec.h"

/*
** \brief execute command using fork/execvpe
** execvpe looks up the PATH before executing a command
** \param cmd
** \param env
** \return
*/
int exec_cmd(char **cmd, char **env)
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

        char buffer[1024];
        sprintf(buffer, "%d", status);
        variables_add("?", buffer);

        return WEXITSTATUS(status);
    }
}