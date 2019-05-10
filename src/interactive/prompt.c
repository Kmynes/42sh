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
#include "../execution/builtins/exit.h"
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

        put_in_history(input);

        if (builtin_exit(input) == true){
            free(input);
            exit(EXIT_SUCCESS);    
        }

        execute_command(input, 0, true);

       

        free(input);
    }
    free(input);
}