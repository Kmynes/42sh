#include <stdio.h>
#include <execution/execute_command.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <execution/execute_command.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.h"
#include "../execution/builtins/42sh_history.h"

void sigintHandler(int sig_num)
{
    sig_num++; // dummy
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
        char* input;

        input = readline("42sh$ ");  // readline allocates space for returned
        // string
        if(input == NULL) {
            break;
        }

        using_history();

        execute_command(input, 0, true);

        put_in_history(input);

        free(input);
    }
    free(input);
}