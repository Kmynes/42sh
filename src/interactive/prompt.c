#include <stdio.h>
#include <execution/execute_command.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"

void create_prompt(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setbuf(stdout, NULL);
    char *input = calloc(1, MAX_INPUT);
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