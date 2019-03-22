#include <stdio.h>
#include <execution/execute_command.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "prompt.h"

void sigintHandler(int sig_num)
{
    sig_num++;
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    printf("\n42sh$ ");
    fflush(stdout);
}

void create_prompt(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setbuf(stdout, NULL);
    char *input = calloc(1, MAX_INPUT);

    signal(SIGINT, sigintHandler);
    while (true)
    {
        printf("42sh$ ");
        size_t i = 0;
        char c;
        while (true)
        {
            c = getchar();

            if (c == '\n')
                break;
            input[i] = c;
            i++;
            if (c == 0 || c == -1)
            {
                break;
            }
        }

        if (i != 0 && (input[0] == 0 || input[0] == -1))
            break;

        execute_command(input, 0);
        memset(input, 0, MAX_INPUT);
    }
}