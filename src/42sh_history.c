#include "42sh_history.h"

int called = 0;

/**
** \file 42sh_history.c
** \brief This function writes in the history file any input in the shell
** \param input: the input of the user
*/
void put_in_history_file(char *input)
{
    char *line = malloc(strlen(input) + 50);
    strcpy(line, input);
    char path_tmp[1024];
    char path_hist[1024];
    char to_tmp[1024];

    getcwd(path_tmp, sizeof(path_tmp));
    getcwd(path_hist, sizeof(path_hist));

    strcat(path_tmp, "/history_tmp");
    strcat(path_hist, "/42sh_history");

    FILE *hist_tmp = fopen(path_tmp, "a+");
    FILE *hist_perm = fopen(path_hist, "a+");

    strcat(line, "\n");
    fprintf(hist_perm, "%s", line);

    sprintf(to_tmp, "\t%d %s", called, line);
    fprintf(hist_tmp, "%s", to_tmp);

    fclose(hist_tmp);
    fclose(hist_perm);

    free(line);

    called++;
}

/**
** \brief This function prints the results of the 'history' command
*/
void read_history(void)
{
    char path_to_tmp[1024];
    char ch;

    getcwd(path_to_tmp, sizeof(path_to_tmp));

    strcat(path_to_tmp, "/history_tmp");

    FILE *hist_tmp = fopen(path_to_tmp, "r");

    for (;(ch = fgetc(hist_tmp)) != EOF ;)
        printf("%c", ch);

    fclose(hist_tmp);
}

/**
** \brief This function ereases the tmp file used for the 'history' command
*/
void erease_tmp_history(void)
{
    char path_to_tmp[1024];

    getcwd(path_to_tmp, sizeof(path_to_tmp));

    strcat(path_to_tmp, "/history_tmp");

    remove(path_to_tmp);
}