#include "exec.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>

int exec_cmd(char **cmd, char **env)
{
    pid_t pid = fork();
    if (pid == -1)
        errx(1, "cannot do fork : an error occured, pid == -1");

    if (pid == 0)
    {
        // child
        execvpe(cmd[0], cmd, env);
        errx(1, "%s: not found", cmd[0]);
    }
    else
    {
        // father
        int status = 0;
        waitpid(pid, &status, 0);

        return status;
    }
}